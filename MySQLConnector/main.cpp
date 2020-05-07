/*
 * Copyright (c) 2015, 2018, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2.0, as
 * published by the Free Software Foundation.
 *
 * This program is also distributed with certain software (including
 * but not limited to OpenSSL) that is licensed under separate terms,
 * as designated in a particular file or component or in included license
 * documentation.  The authors of MySQL hereby grant you an
 * additional permission to link the program and your derivative works
 * with the separately licensed software that they have included with
 * MySQL.
 *
 * Without limiting anything contained in the foregoing, this file,
 * which is part of MySQL Connector/C++, is also subject to the
 * Universal FOSS Exception, version 1.0, a copy of which can be found at
 * http://oss.oracle.com/licenses/universal-foss-exception.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License, version 2.0, for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
 */

#include <iostream>
#include <list>
#include <mysqlx/xdevapi.h>

// BOOST Libs
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>


using ::std::cout;
using ::std::endl;
using namespace ::mysqlx;
namespace pt = boost::property_tree;

class MySqlDatabase {
public:
    MySqlDatabase (const std::string& ip, const unsigned int port)
        : ip_address_(ip), port_(port)
    {
        connect();
      // Get a list of all available schemas
      std::list<Schema> schemaList = session_->getSchemas();

      cout << "Available schemas in this session:" << endl;

      // Loop over all available schemas and print their name
      for (Schema schema : schemaList) {
        cout << schema.getName() << endl;
      }
    };

    ~MySqlDatabase ()
    {
        session_->close();
        delete session_;
    };

     // CRUD operators for Collections
     void add ()
     {

     };

     void find ()
     {

     };

     void modify ()
     {

     };

     // CRUD operators for Tables
    void create ()
    {

    };

private:
    void connect ()
    {
        try {
                // Connect to MySQL Server on a network machine
                // *** CHANGE TO SOMETHING SECURE BEFORE IMPLEMENTING
                session_ = new Session (SessionOption::HOST, ip_address_,
                                  SessionOption::PORT, port_,
                                  SessionOption::USER, "root",
                                  SessionOption::PWD, "root");
                //Schema sep_schema(*session_, "SmartEnergyProfile");
            }
            catch (std::exception &ex)
            {
              cout <<"STD EXCEPTION: " << ex.what() <<endl;
            }
    }

    std::string ip_address_;
    unsigned int port_;
    Session* session_;
};


int main(int argc, const char* argv[])
{
    MySqlDatabase MySqlDB("127.0.0.1", 33060);

    // Use boosts xml parser to read file and store as member variable.
    pt::ptree sep_xsd;
    pt::xml_parser::read_xml("sep.xsd", sep_xsd);

    // map SEP elements
    std::vector <std::string> elements;
    BOOST_FOREACH(pt::ptree::value_type const& row, sep_xsd.get_child("xs:schema"))
    {
        if (row.first == "xs:element")
        {
            std::string name = row.second.get <std::string> ("<xmlattr>.name", "DEFAULT_NAME");
            elements.push_back(name);
        }
    }

    BOOST_FOREACH(pt::ptree::value_type const& row, sep_xsd.get_child("xs:schema"))
    {
        if (row.first == "xs:element")
        {
            std::string name = row.second.get <std::string> ("<xmlattr>.name", "DEFAULT_NAME");
            elements.push_back(name);
        }
    }
    return 0;
}

