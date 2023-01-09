#include "nim_learner.h"
#include <ctime>

NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
  for (unsigned t = 0; t <= startingTokens; t++) {
    Vertex v1 = "p1-" + to_string(t);
    Vertex v2 = "p2-" + to_string(t);
		g_.insertVertex(v1);
		g_.insertVertex(v2);
  }

  std::vector<Vertex> verts = g_.getVertices();
  for (Vertex vert: verts) {
    std::string player = vert.substr(0, 3);
    int token = stoi(vert.substr(3));

    std::string next_player = "";
    if (player == "p1-") {
      next_player = "p2-";
    } else {
      next_player = "p1-";
    }

    if (token >= 2) {
      g_.insertEdge(vert, next_player + to_string(token - 1));
      g_.setEdgeWeight(vert, next_player + to_string(token - 1), 0);

      g_.insertEdge(vert, next_player + to_string(token - 2));
      g_.setEdgeWeight(vert, next_player + to_string(token - 2), 0);
    } else if (token == 1) {
      g_.insertEdge(vert, next_player + to_string(token - 1));
      g_.setEdgeWeight(vert, next_player + to_string(token - 1), 0);
    }
  }
  startingVertex_ = "p1-" + to_string(startingTokens);
}

std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
  Vertex curr = startingVertex_;
  std::vector<Vertex> adj = g_.getAdjacent(curr);

  while (!adj.empty()) {
    Vertex next_vert = adj[rand() % adj.size()];
    path.push_back(g_.getEdge(curr, next_vert));
    adj = g_.getAdjacent(next_vert);
    curr = next_vert;
  }
  return path;
}

void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
  Vertex loser = path[path.size() - 1].dest;

  bool p1_win = false;
  if  (loser == "p2-0") {
    p1_win = true;
  }

  for (Edge edge: path) {
    int weight = g_.getEdgeWeight(edge.source, edge.dest);
    if (edge.source.substr(0,2) == "p1") {
      if (p1_win) {
        weight += 1;
      } else {
        weight -= 1;
      }
    } else {
      if (p1_win) {
        weight -= 1;
      } else {
        weight += 1;
      }
    }
    g_.setEdgeWeight(edge.source, edge.dest, weight);
  }
}

void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

const Graph & NimLearner::getGraph() const {
  return g_;
}