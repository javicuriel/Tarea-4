//
//  main.cpp
//  Tarea-4
//
//  Created by Javier Curiel on 10/27/15.
//  Copyright © 2015 Javier Curiel. All rights reserved.
//

#include "Snap.h"
#include <iostream>
#include <fstream>
#include <chrono>


using namespace std;
void GraphML(PNGraph g);
void GEXF(PNGraph g);
void GDF(PNGraph g);
void JSON(PNGraph g);

int main() {
    PNGraph grafo = TSnap::LoadEdgeList<PNGraph>("/Users/javiercuriel/Desktop/Tarea-4/examples/XcodeTest/XcodeTest/facebook_combined.txt",0,1);
    
    auto begin = std::chrono::high_resolution_clock::now();
    GraphML(grafo);
    auto end = std::chrono::high_resolution_clock::now();
    auto ml = chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    std::cout << "GraphML: " << ml.count() << " ms"<< std::endl;
    
    begin = std::chrono::high_resolution_clock::now();
    GEXF(grafo);
    end = std::chrono::high_resolution_clock::now();
    auto gexf = chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    std::cout << "GEXF: " << gexf.count() << " ms"<<  std::endl;
    
    begin = std::chrono::high_resolution_clock::now();
    GDF(grafo);
    end = std::chrono::high_resolution_clock::now();
    auto gdf = chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    std::cout << "GDF: " << gdf.count() << " ms" << std::endl;
    
    begin = std::chrono::high_resolution_clock::now();
    JSON(grafo);
    end = std::chrono::high_resolution_clock::now();
    auto json = chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    std::cout << "JSON: " << json.count() << " ms" << std::endl;
    
    return 0;
}

void GraphML(PNGraph g){
    ofstream data ("/Users/javiercuriel/Desktop/Tarea-4/examples/XcodeTest/XcodeTest/facebook_combined.graphml");
    if (data.is_open()) {
        data << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        data << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
        data << "<graph id=\"G\" edgedefault=\"directed\">\n";
        for (PNGraph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
            data << "<node id=\"" << NI.GetId() << "\"/>\n";
        int i = 1;
        for (PNGraph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++, ++i)
            data << "<edge id=\"e" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\"/>\n";
        data << "</graph>\n";
        data << "</graphml>\n";
        data.close();
    }
}

void GEXF(PNGraph g){
    ofstream data ("/Users/javiercuriel/Desktop/Tarea-4/examples/XcodeTest/XcodeTest/facebook_combined.gexf");
    if (data.is_open()) {
        data << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        data << "<gexf xmlns=\"http://www.gexf.net/1.2draft\" version=\"1.2\">\n";
        data << "<graph mode=\"static\" defaultedgetype=\"directed\">\n";
        data << "<nodes>\n";
        for (PNGraph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
            data << "<node id=\"" << NI.GetId() << "\" />\n";
        data << "</nodes>\n";
        data << "<edges>\n";
        int i = 1;
        for (PNGraph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++, ++i)
            data << "<edge id=\"" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\" />\n";
        data << "</edges>\n";
        data << "</graph>\n";
        data << "</gexf>\n";
        data.close();
    }
}

void GDF(PNGraph g){
    ofstream data ("/Users/javiercuriel/Desktop/Tarea-4/examples/XcodeTest/XcodeTest/facebook_combined.gdf");
    if (data.is_open()) {
        data << "nodedef> namege\n";
        for (PNGraph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
            data << NI.GetId() << "\n";
        data << "edgedef>source VARCHAR, destination VARCHAR\n";
        for (PNGraph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++)
            data << EI.GetSrcNId() << ", " << EI.GetDstNId() << "\n";
        data.close();
    }
}

void JSON(PNGraph g){
    ofstream data ("/Users/javiercuriel/Desktop/Tarea-4/examples/XcodeTest/XcodeTest/facebook_combined.json");
    if (data.is_open()) {
        data << "{ \"graph\": {\n";
        data << "\"nodes\": [\n";
        for (PNGraph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); ){
            data << "{ \"id\": \"" << NI.GetId() << "\" }";
            if (NI++ == g->EndNI())
                data << " ],\n";
            else
                data << ",\n";
        }
        data << "\"edges\": [\n";
        for (PNGraph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); ){
            data << "{ \"source\": \"" << EI.GetSrcNId() << "\", \"target\": \"" << EI.GetDstNId() << "\" }";
            if (EI++ == g->EndEI())
                data << " ]\n";
            else
                data << ",\n";
        }
        data << "} }";
        data.close();
    }
}