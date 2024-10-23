#ifndef TREEMERKLE_H
#define TREEMERKLE_H

#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QCryptographicHash>

using namespace std;

// Definición de un nodo en el Árbol de Merkle
struct NodeMerkle {
    string hash;
    NodeMerkle* left;
    NodeMerkle* right;

    NodeMerkle(const string& data) : hash(data), left(nullptr), right(nullptr) {}
};

// Implementación básica del algoritmo SHA-256 (simplificado para fines didácticos)
string sha256(const string &input) {
    // Simulación de SHA-256 para hacerlo más sencillo
    QString data = QString::fromStdString(input);
    QByteArray hashData = QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Sha256);
    data = hashData.toHex();

    return data.toStdString();
}

NodeMerkle* combineNodes(NodeMerkle* left, NodeMerkle* rigth){
    string combineHash = sha256(left->hash + rigth->hash);
    NodeMerkle* parent = new NodeMerkle(combineHash);
    parent->left = left;
    parent->right = rigth;
    return parent;
}

// Función recursiva para construir el Árbol de Merkle
NodeMerkle* buildMerkleTree(NodeMerkle** leaves, int start, int end) {
    // Si solo hay una hoja, retorna el nodo hoja
    if (start == end) {
        return leaves[start];
    }

    // Encuentra el punto medio para dividir la lista de hojas
    int mid = (start + end) / 2;

    // Construir el subárbol izquierdo y derecho de manera recursiva
    NodeMerkle* leftSubTree = buildMerkleTree(leaves, start, mid);
    NodeMerkle* rightSubTree = buildMerkleTree(leaves, mid + 1, end);

    // Combinar los dos subárboles en un nodo padre
    return combineNodes(leftSubTree, rightSubTree);
}

// Ruta base constante para almacenar los archivos .dot y .png
 QString baseFilePath = "C:/Users/matth/OneDrive/Documentos/Proyectos C++/EDD_Proyectos_202202233/Proyecto_Fase3/Fase3/reportes/";

// Función para generar el archivo .dot para Graphviz
void generateDotFile(NodeMerkle* node, QTextStream &outFile, int& nodeCounter) {
    if (!node) return;

    int currentNode = nodeCounter++;
    outFile << "node" << currentNode << " [label=\"" << QString::fromStdString(node->hash) << "\"];\n";

    if (node->left) {
        int leftNode = nodeCounter;
        outFile << "node" << currentNode << " -- node" << leftNode << ";\n";
        generateDotFile(node->left, outFile, nodeCounter);
    }

    if (node->right) {
        int rightNode = nodeCounter;
        outFile << "node" << currentNode << " -- node" << rightNode << ";\n";
        generateDotFile(node->right, outFile, nodeCounter);
    }
}

// Función para generar el gráfico del Árbol de Merkle
void graphMerkleTree(NodeMerkle* root) {
    // Archivo .dot y archivo .png basados en la ruta base
    QString dotFilePath = baseFilePath + "treeMerkle.dot";
    QString imagePath = baseFilePath + "treeMerkle.png";

    // Crear y abrir el archivo .dot
    QFile outFile(dotFilePath);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("No se pudo abrir el archivo .dot para escribir");
        return;
    }

    QTextStream outStream(&outFile);
    outStream << "graph MerkleTree {\n";

    int nodeCounter = 0;
    generateDotFile(root, outStream, nodeCounter);

    outStream << "}\n";
    outFile.close();

    // Ejecutar el comando de Graphviz usando QProcess
    QProcess process;
    QStringList args;
    args << "-Tpng" << dotFilePath << "-o" << imagePath;
    process.start("dot", args);
    process.waitForFinished();

    if (process.exitCode() == 0) {
        qDebug() << "Árbol de Merkle graficado en" << imagePath;
    } else {
        qWarning() << "Error al ejecutar Graphviz:" << process.readAllStandardError();
    }
}

#endif // TREEMERKLE_H
