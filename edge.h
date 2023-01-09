#pragma once

#include <string>
#include <limits.h>

using std::string;

typedef string Vertex;

//Represents an edge in a graph; used by the Graph class.
class Edge {
public:
  Vertex source; /**< The source of the edge **/
  Vertex dest; /**< The destination of the edge **/

  Edge(Vertex u, Vertex v)
    : source(u), dest(v), label(""), weight(-1) {}

  //@param lbl - the edge label
  Edge(Vertex u, Vertex v, string lbl)
    : source(u), dest(v), label(lbl), weight(-1) {}
  
  //@param w - the weight of the edge
  Edge(Vertex u, Vertex v, int w, string lbl)
    : source(u), dest(v), label(lbl), weight(w) {}

  //Default constructor.
  Edge() : source(""), dest(""), label(""), weight(-1) {}

  //Compares two Edges.
  //operator< is defined so Edges can be sorted with std::sort.
  //@param other - the edge to compare with
  //@return whether the current edge is less than the parameter
  bool operator<(const Edge& other) const {
    return weight < other.weight;
  }

  string getLabel() const {
    return this->label;
  }

  int getWeight() const {
    return this->weight;
  }

  //Compares two edges' source and dest.
  //@param other - the edge to compare with
  bool operator==(Edge& other) const {
    if (this->source != other.source)
      return false;
    if (this->dest != other.dest)
      return false;
    return true;
  }

private:
  string label; //The edge label
  int weight; //The edge weight (if weighted graph)
};