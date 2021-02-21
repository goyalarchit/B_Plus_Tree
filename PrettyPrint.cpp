#include"PrettyPrint.h"



void BPTreePrinter::visit (Node const *node, unsigned level, unsigned child_index)
{
   if (level >= levels.size())
      levels.resize(level + 1);

   LevelInfo &level_info = levels[level];
   NodeInfo info;

   info.text_pos = 0;
   if (!level_info.empty())  // one blank between nodes, one extra blank if left-most child
      info.text_pos = level_info.back().text_end + (child_index == 0 ? 2 : 1);

   info.text = node_text(node->key, unsigned(node->size));

   if (node->isLeaf)
   {
      info.text_end = info.text_pos + unsigned(info.text.length());
   }
   else // non-leaf -> do all children so that .text_end for the right-most child becomes known
   {
      for (unsigned i = 0, e = unsigned(node->size); i <= e; ++i)  // one more pointer than there are keys
         visit(node->ptr[i], level + 1, i);

      info.text_end = levels[level + 1].back().text_end;
   }

   levels[level].push_back(info);
}


std::string BPTreePrinter::node_text (int const keys[], unsigned key_count)
{
   std::ostringstream os;
   char const *sep = "";

   os << "[";
   for (unsigned i = 0; i < key_count; ++i, sep = " ")
      os << sep << keys[i];
   os << "]";

   return os.str();
}

void print_blanks (unsigned n)
{
   while (n--)
      std::cout << ' ';
}

void BPTreePrinter::after_traversal ()
{
   for (std::size_t l = 0, level_count = levels.size(); ; )
   {    
      auto const &level = levels[l];
      unsigned prev_end = 0;

      for (auto const &node: level)
      {         
         unsigned total = node.text_end - node.text_pos;
         unsigned slack = total - unsigned(node.text.length());
         unsigned blanks_before = node.text_pos - prev_end;

         print_blanks(blanks_before + slack / 2);
         std::cout << node.text;

         if (&node == &level.back())
            break;

         print_blanks(slack - slack / 2);

         prev_end += blanks_before + total;
      }

      if (++l == level_count)
         break;

      std::cout << "\n\n";
   }

   std::cout << "\n";
}