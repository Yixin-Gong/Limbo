#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <limits>

namespace ContestFileParser
{
    using std::cerr;
    using std::cout;
    using std::endl;
    using std::make_pair;
    using std::ostream;
    using std::pair;
    using std::string;
    using std::vector;
    typedef int int32_t;
    typedef unsigned int uint32_t;
    typedef long int64_t;

    /// @brief Temporary data structures to hold parsed data.
    /// Base class for all temporary data structures.
    struct Item
    {
        /// print data members
        virtual void print(ostream &) const {};
        /// print data members with stream operator
        /// @param ss output stream
        /// @param rhs target object
        /// @return output stream
        friend ostream &operator<<(ostream &ss, Item const &rhs)
        {
            rhs.print(ss);
            return ss;
        }
    };

    /// @brief shape box to describe one node shape
    struct ShapeBox : public Item
    {
        string name;      ///< shape name
        double origin[2]; ///< lower left corner of the box
        double size[2];   ///< width and height
        bool isMacro;

        /// @brief constructor
        /// @param n shape name
        /// @param x lower left coordinate
        /// @param y lower left coordinate
        /// @param w width
        /// @param h height
        /// @param flag macro flag
        ShapeBox(string &n, double x, double y, double w, double h, bool flag)
        {
            name.swap(n);
            origin[0] = x;
            origin[1] = y;
            size[0] = w;
            size[1] = h;
            isMacro = flag;
        }
        /// reset all data members
        void reset()
        {
            name = "";
            origin[0] = origin[1] = 0;
            size[0] = size[1] = 0;
            isMacro = 0;
        }
    };

    /// @brief node shape to describe the shapes of node
    struct NodeShape : public Item
    {
        string node_name; ///< node name
        vector<ShapeBox> vShapeBox; 
        bool macro_flag = 0;
        /// reset all data members
        void reset()
        {
            node_name = "";
            vShapeBox.clear();
        }
        /// print data members
        /// @param ss output stream
        virtual void print(ostream &ss) const
        {
            ss << "//////// NodeShape ////////" << endl
               << "node_name = " << node_name << endl;
            for (uint32_t i = 0; i < vShapeBox.size(); ++i)
                ss << vShapeBox[i].name
                   << " @(" << vShapeBox[i].origin[0] << ", " << vShapeBox[i].origin[1] << ") "
                   << " w/h (" << vShapeBox[i].size[0] << ", " << vShapeBox[i].size[1] << ")" << endl
                   << "macro:" << vShapeBox[i].isMacro
                   << endl;
            ss << endl;
        }
    };

    /// @brief placement row
    struct Row : public Item
    {
        int32_t origin[2];   ///< x, y
        int32_t length;      ///< row length
        int32_t height;      ///< row height
        int32_t repeatCount; ///< repeat count
        /// constructor
        Row()
        {
            reset();
        }
        /// reset all data members
        void reset()
        {
            origin[0] = origin[1] = -1;
            length = 0;
            height = 0;
            repeatCount = 0;
        }
        /// print data members
        /// @param ss output stream
        virtual void print(ostream &ss) const
        {
            ss << "//////// Row ////////" << endl
               << "origin = " << origin[0] << " " << origin[1] << endl
               << "row length = " << length << endl
               << "row height = " << height << endl
               << "repeat count = " << repeatCount << endl;
        }
    };

    /// @brief describe a pin of a net
    struct NetPin : public Item
    {
        string node_name; ///< node name
        string pin_name;  ///< pin name
        char direct;      ///< direction
        double offset[2]; ///< offset (x, y) to node origin
        double size[2];   ///< sizes (x, y) of pin

        /// constructor
        NetPin()
        {
            node_name = "";
            pin_name = "";
            direct = '\0';
            offset[0] = 0;
            offset[1] = 0;
            size[0] = 0;
            size[1] = 0;
        }
        /// constructor
        /// @param nn node name
        /// @param d direction
        /// @param x, y offset of pin to node origin
        /// @param w, h size of pin
        /// @param pn pin name
        NetPin(string &nn, char d, double x, double y, double w, double h, string &pn)
        {
            node_name.swap(nn);
            direct = d;
            offset[0] = x;
            offset[1] = y;
            size[0] = w;
            size[1] = h;
            pin_name.swap(pn);
        }
        /// constructor
        /// @param nn node name
        /// @param d direction
        /// @param x, y offset of pin to node origin
        /// @param w, h size of pin
        NetPin(string &nn, char d, double x, double y, double w, double h)
        {
            node_name.swap(nn);
            direct = d;
            offset[0] = x;
            offset[1] = y;
            size[0] = w;
            size[1] = h;
            pin_name.clear();
        }
        /// reset all data members
        void reset()
        {
            node_name = "";
            pin_name = "";
            direct = '0';
            offset[0] = offset[1] = 0;
            size[0] = size[1] = 0;
        }
    };



}