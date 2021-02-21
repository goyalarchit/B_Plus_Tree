#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<sstream>
#include"BPTree.h"
using namespace std;

class BPTreePrinter
{
   struct NodeInfo
   {
      std::string text;
      unsigned text_pos, text_end;  // half-open range
   };

   typedef std::vector<NodeInfo> LevelInfo;

   std::vector<LevelInfo> levels;

   std::string node_text (int const keys[], unsigned key_count);

   void before_traversal ()
   {
      levels.resize(0);
      levels.reserve(10);   // far beyond anything that could usefully be printed
   }

   void visit (Node const *node, unsigned level = 0, unsigned child_index = 0);

   void after_traversal ();

public:
   void print (BPTree const &tree)
   {
      before_traversal();
      visit(tree.root);
      after_traversal();
   }
};