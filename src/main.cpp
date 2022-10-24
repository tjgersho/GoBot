//
//  main.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/27/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.

// #include <boost/lambda/lambda.hpp>
// #include <boost/filesystem/path.hpp>
// #include <boost/locale.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

// #include <cstdlib>
// #include <memory>
// #include <utility>
// #include <boost/asio.hpp>
 
// #include <ctime>

// #include <iterator>
// #include <algorithm>

// #include <iostream>
// #include "Node.hpp"
// #include "Sensor.hpp"
// #include "iNet.hpp"
// #include "Brain.hpp"
// #include "Edge.hpp"
// #include "MetaBrain.hpp"

// #ifdef _WIN32 
// #include <SDL.h>
// #else
// #include <SDL2/SDL.h>
// #endif

// #include <chrono>
// #include <thread>

// #include "GOL.hpp"
// #include <math.h>
// #include "Screen.hpp"
// #include <stdlib.h>
// #include <time.h>
// #include <map>
// #include "SDLWindow.hpp"
// #include <memory>
// #include "GoBotWin.hpp"

// #include <thread>
#include "GoBot.hpp"

// #include "Label.hpp"
#include "Utils.hpp"

// #include "QuadBox.hpp"
// #include <cassert>
// #include <chrono>
// #include <iostream>
// #include <random>
// #include "QuadTree.hpp"

#undef main // This is needed because linker is confused by the main in the SDL library
 

//  using boost::asio::ip::tcp;

// class session : public std::enable_shared_from_this<session>
// {
// public:
//   session(tcp::socket socket)
//     : socket_(std::move(socket))
//   {
//   }

//   void start()
//   {
//     do_read();
//   }

// private:
//   void do_read()
//   {
//     auto self(shared_from_this());
//     socket_.async_read_some(boost::asio::buffer(data_, max_length),
//         [this, self](boost::system::error_code ec, std::size_t length)
//         {
//           if (!ec)
//           {
//             do_write(length);
//           }
//         });
//   }

//   void do_write(std::size_t length)
//   {
//     auto self(shared_from_this());
//     boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
//         [this, self](boost::system::error_code ec, std::size_t /*length*/)
//         {
//           if (!ec)
//           {
//             do_read();
//           }
//         });
//   }

//   tcp::socket socket_;
//   enum { max_length = 1024 };
//   char data_[max_length];
// };

// class server
// {
// public:
//   server(boost::asio::io_service& io_service, short port)
//     : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
//       socket_(io_service)
//   {
//     do_accept();
//   }

// private:
//   void do_accept()
//   {
//     acceptor_.async_accept(socket_,
//         [this](boost::system::error_code ec)
//         {
//           if (!ec)
//           {
//             std::make_shared<session>(std::move(socket_))->start();
//           }

//           do_accept();
//         });
//   }

//   tcp::acceptor acceptor_;
//   tcp::socket socket_;
// };


// class X {
//     public:
//         void setProtMemb( int i ) { m_protMemb = i; }
//         void Display() { 
            
//                 std::cout << m_protMemb << std::endl;
//                 Protfunc();
            
//             }
//     protected:
//         int  m_protMemb;
//         void Protfunc() { std::cout << "\nAccess allowed\n"; }
// } x;

// class Y : public X {
//     public:
//         void useProtfunc() { Protfunc(); }
// } y;


// class S
// {
// private:
//     int n; // S::n is private
// protected:
//     void setN(int j){n=j;}
// public:
//     S() : n(10) {}                    // this->n is accessible in S::S
//     S(int i){n=i;}
//     S(const S& other) : n(other.n) {} // other.n is accessible in S::S

//     void goodSetN(int l){
//         setN(l);
//     }

//     int getN(){
//         return n;
//     }
// };
 

// class Song
// {
// public:

//     Song(int track){
//         _track = track;
//     }
//     void Play(){
//          std::cout << "Playing Current Track: "<< _track << std::endl;
//     }
//     void PrintStr(std::string str){
//         std::cout << str << std::endl;
//     }
// private:
//     int _track;
 
// };

// class Album{
//     public:
//         std::vector<std::shared_ptr<Song>> songs;
//         bool playing = false;

//         void addTrack(std::shared_ptr<Song> s){
//             songs.push_back(s);
//         }

//         void Play(int songIndex){
//             playing = true;

//             int currentTrack = songIndex;
//             int fullAlbumPlayCount = 0;
//             while(playing){
                
//                 songs[currentTrack]->Play();

//                 currentTrack++;

//                 if(currentTrack >= songs.size()){
//                     currentTrack = 0;
//                 }

//                 if(fullAlbumPlayCount >= songs.size() ){
//                     break;
//                 }

//                 fullAlbumPlayCount++;
//             }
//         }
// };

// class Studio {
//     public:
//         std::shared_ptr<Album> createAlbum(){
//             auto a = std::make_shared<Album>();
//             for(int i=0; i<5; i++){
//                 a->addTrack(std::make_shared<Song>(i));
//             }
//             return a;
//         }
// };

// void testFunc(Song* song){
 
//     song->PrintStr("testFunc");
// }

// void testFunc1(std::shared_ptr<Song> song){
 
//     song->PrintStr("TestFunc1");

//     song.reset();
// }



// void testFunc2(std::unique_ptr<Song>& song){
 
//     song->PrintStr("TestFunc2");

//     song.release();
// }




// struct QuadNode
// {
//     QuadBox<float> box;
//     std::size_t id;
// };

// std::vector<QuadNode> generateRandomNodes(std::size_t n)
// {
//     auto generator = std::default_random_engine();
//     auto originDistribution = std::uniform_real_distribution(0.0f, 1.0f);
//     auto sizeDistribution = std::uniform_real_distribution(0.0f, 0.01f);
//     auto nodes = std::vector<QuadNode>(n);
//     for (auto i = std::size_t(0); i < n; ++i)
//     {
//         nodes[i].box.left = originDistribution(generator);
//         nodes[i].box.top = originDistribution(generator);
//         nodes[i].box.width = std::min(1.0f - nodes[i].box.left, sizeDistribution(generator));
//         nodes[i].box.height = std::min(1.0f - nodes[i].box.top, sizeDistribution(generator));
//         nodes[i].id = i;
//     }
//     return nodes;
// }

// std::vector<std::pair<QuadNode*, QuadNode*>> computeIntersections(std::vector<QuadNode>& nodes, const std::vector<bool>& removed)
// {
//     auto intersections = std::vector<std::pair<QuadNode*, QuadNode*>>();
//     for (auto i = std::size_t(0); i < nodes.size(); ++i)
//     {
//         if (removed.size() == 0 || !removed[i])
//         {
//             for (auto j = std::size_t(0); j < i; ++j)
//             {
//                 if (removed.size() == 0 || !removed[j])
//                 {
//                     if (nodes[i].box.intersects(nodes[j].box))
//                         intersections.emplace_back(&nodes[i], &nodes[j]);
//                 }
//             }
//         }
//     }
//     return intersections;
// }

// void checkIntersections(std::vector<QuadNode*> nodes1, std::vector<QuadNode*> nodes2)
// {
//     assert(nodes1.size() == nodes2.size());
//     std::sort(std::begin(nodes1), std::end(nodes1));
//     std::sort(std::begin(nodes2), std::end(nodes2));
//     for (auto i = std::size_t(0); i < nodes1.size(); ++i)
//         assert(nodes1[i] == nodes2[i]);
// }

// int range(int a, int b)
// {
//     static long long int i;
//     static int state = 0;
//     switch (state) {
//     case 0: /* start of function */
//         state = 1;
//         for (i = a; i < b; i++) {
//             return i;
 
//         /* Returns control */
//         case 1:
//             std::cout << "control at range"
//                  << std::endl; /* resume control straight
//                            after the return */
//         }
//     }
//     state = 0;
//     return 0;
// }



/////////////////////////////////////////////////////////////
// gps coordinate
//
// illustrates serialization for a simple type
//
 
#include "GoNode.hpp"
#include "GoNet.hpp"


// #include <stdio.h>
// #include <string.h>
// #include "tinyfiledialogs.cpp"

int main(int argc, char**argv) {
 
  // create and open a character archive for output
    boost::uuids::random_generator uuidGen;
 
 
    auto g1 = std::make_shared<GoNode>();
    boost::uuids::uuid uuid = uuidGen();
    std::stringstream uuidStrm;
    uuidStrm << uuid;

    g1->id  = uuidStrm.str();
 
    g1->label = "11111111";
    g1->activation = 12.4;
    g1->sensorNode = true;

   

    boost::uuids::uuid uuid1 = uuidGen();
    std::stringstream uuidStrm1;
    uuidStrm1 << uuid1;

    auto g2 = std::make_shared<GoNode>();
    g2->id =  uuidStrm1.str();
    g2->label = "22222222";
    g2->activation = 1.4;
    g2->sensorNode = true;


    for(int i=0; i<100; i++){
        boost::uuids::uuid uuidEdge;
        std::stringstream uuidStrm0;
        uuidStrm0 << uuidEdge;
        std::string uuidStr = uuidStrm0.str();
        g1->iEdges.insert(std::pair<std::string, bool>(uuidStr, true));
        g1->oEdges.insert(std::pair<std::string, bool>(uuidStr, false));

        g2->iEdges.insert(std::pair<std::string, bool>(uuidStr, false));
        g2->oEdges.insert(std::pair<std::string, bool>(uuidStr, true));
    }
 
    auto net1 = std::make_shared<GoNet>();
    net1->id = "Net_1111";
    net1->nodes.insert(std::pair<std::string, std::shared_ptr<GoNode>>(g1->id, g1));
    net1->nodes.insert(std::pair<std::string, std::shared_ptr<GoNode>>(g2->id, g2));

  // //Write archive to text..
    std::string gobotfile = Utils::saveGoBot();

    GoBot bot1;


    bot1.goBrain->nets.insert(std::pair<std::string, std::shared_ptr<GoNet>>(net1->id, net1));
    
    // save data to archive
    {
        std::ofstream ofs("net1.txt");
        // std::ostream os("")
        boost::archive::text_oarchive oa(ofs);

        // write class instance to archive
        oa << *net1;
        ofs.close();
    	// archive and stream closed when destructors are called
    }

   
    // save data to archive
    {
        std::ofstream ofs(gobotfile);
        // std::ostream os("")
        boost::archive::text_oarchive oa(ofs);

        // write class instance to archive
        oa << bot1;
        ofs.close();
    	// archive and stream closed when destructors are called
    }


    // ... some time later restore the class instance to its orginal state
    GoNet newnet;
    {
        // create and open an archive for input
        std::ifstream ifs("net1.txt");
        boost::archive::text_iarchive ia(ifs);
        // read class state from archive
        ia >> newnet;
        // archive and stream closed when destructors are called
    }


    GoBot newbot;
    {
        // create and open an archive for input
        std::ifstream ifs(gobotfile);
        boost::archive::text_iarchive ia(ifs);
        // read class state from archive
        ia >> newbot;
        // archive and stream closed when destructors are called
    }


    std::cout << "Serialization - Activation" << std::endl;

    std::cout << newnet.id <<std::endl;
    for(auto const& [id, node] : newnet.nodes){
        std::cout <<  node->activation << std::endl;
        std::cout  << node->sensorNode << std::endl;
        std::cout << node->label <<  "   " <<  std::endl;
        std::cout << "--------------------" << std::endl;
    }
    

    assert(newnet.nodes.at(uuidStrm.str())->id == uuidStrm.str());
    assert(newnet.nodes.at(uuidStrm.str())->activation == g1->activation);
    assert(newnet.nodes.at(uuidStrm.str())->sensorNode == g1->sensorNode);
    assert(newnet.nodes.at(uuidStrm.str())->label == g1->label);
   /// assert(newnet.nodes.at("1")->id == g1->id);

    assert(newnet.nodes.at(uuidStrm1.str())->activation == g2->activation);
    assert(newnet.nodes.at(uuidStrm1.str())->sensorNode == g2->sensorNode);
    assert(newnet.nodes.at(uuidStrm1.str())->label == g2->label);
    assert(newnet.nodes.at(uuidStrm1.str())->id == g2->id);
    assert(newnet.nodes.at(uuidStrm1.str())->id == uuidStrm1.str());

    for(auto [id, edge] : newnet.nodes.at(uuidStrm.str())->iEdges){
        assert( edge );
    }

    for(auto [id, edge] : newnet.nodes.at(uuidStrm.str())->oEdges){
        assert( !edge );
    }

    for(auto [id, net] : newbot.goBrain->nets){
        assert(newbot.goBrain->nets[id]->id == net->id);
        assert(id == "Net_1111");
    }

    std::cout << "EVERYTHING GOOD HERE:)" << std::endl;
    return 0;


    // int i; // For really large numbers
 
    // for (; i = range(1, 5);)
    //     std::cout << "control at main :" << i << std::endl;
 
    // return 0;

// try
//   {
//     if (argc != 2)
//     {
//       std::cerr << "Usage: async_tcp_echo_server <port>\n";
//       return 1;
//     }

//     boost::asio::io_service io_service;

//     server s(io_service, std::atoi(argv[1]));

//     io_service.run();
//   }
//   catch (std::exception& e)
//   {
//     std::cerr << "Exception: " << e.what() << "\n";
//   }

//   return 0;


    //  using namespace boost::locale;
    // using namespace std;
    // generator gen;
    // locale loc=gen(""); 
    // // Create system default locale

    // locale::global(loc); 
    // // Make it system global
    
    // cout.imbue(loc);
    // // Set as default locale for output
    
    // cout <<format("Today {1,date} at {1,time} we had run our first localization example") % time(0) 
    //       <<endl;
   
    // cout<<"This is how we show numbers in this locale "<<as::number << 103.34 <<endl; 
    // cout<<"This is how we show currency in this locale "<<as::currency << 103.34 <<endl; 
    // cout<<"This is typical date in the locale "<<as::date << std::time(0) <<endl;
    // cout<<"This is typical time in the locale "<<as::time << std::time(0) <<endl;
    // cout<<"This is upper case "<<to_upper("Hello World!")<<endl;
    // cout<<"This is lower case "<<to_lower("Hello World!")<<endl;
    // cout<<"This is title case "<<to_title("Hello World!")<<endl;
    // cout<<"This is fold case "<<fold_case("Hello World!")<<endl;

//      x.setProtMemb( 12 );   // OK, uses public access function
//    x.Display();      //   error, m_protMemb is protected
  
//    x.Display();
//    y.setProtMemb( 5 );   // OK, uses public access function
//    y.Display();
//    // x.Protfunc();         error, Protfunc() is protected
//    y.useProtfunc();

//    S vmmm = S(1); 

//    vmmm.goodSetN(12);
    
//    std::cout << "vmmm.getN()" <<std::endl;

//    std::cout << vmmm.getN() <<std::endl;



    // Label nLabel;
    // nLabel.text = "Fun Times";
    // nLabel.drawSelf();

    // Label ch1Label;
    // ch1Label.text = "MORE Fun 2XTime";

    // Label ch2Label;
    // ch2Label.text = "MORE Fun 3XTime";
    // nLabel.children.push_back(&ch1Label);
    // nLabel.children.push_back(&ch2Label);

  

    // nLabel.drawSelf();

    //   ch2Label.drawSelf();
    //     ch2Label.drawSelf();

    //  return 1;

    // Declare a smart pointer on stack and pass it the raw pointer.
    // std::unique_ptr<Song> song2(new Song());

    // std::shared_ptr<Song> song3(new Song());

    // // Use song2...
    //  (*song2).DoSomething();


    // testFunc2(song2);

    // song2->PrintStr("2 DONE");

    // testFunc1(song3);

    //song3->PrintStr("3 DONE");

    // Album a;
    // std::shared_ptr<Song> s = std::shared_ptr<Song>(new Song(0));
    // a.songs.push_back(s);
    // for(int i=1; i<10; i++){
    //     a.addTrack(std::make_shared<Song>(i));
    // }

    // s->Play();

    // Album a1;

    // a1.songs.push_back(s);

    // a.Play(2);
 
    // a1.Play(0);

    // Studio st;

    // auto b = st.createAlbum();

    // b->songs.push_back(s);

    // b->Play(0);

    // GoBotWindow gowin;

    // gowin.init();
    
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // auto n = std::size_t(1000);
    // auto getBox = [](QuadNode* node)
    // {
    //     return node->box;
    // };
    // auto box = QuadBox(0.0f, 0.0f, 1.0f, 1.0f);
    // auto nodes = generateRandomNodes(n);
    // // Add nodes to quadtree
    // auto quadtree = QuadTree<QuadNode*, decltype(getBox)>(&box, getBox);
    // auto start1 = std::chrono::steady_clock::now();
    // for (auto& node : nodes)
    //     quadtree.add(&node);
    // // Randomly remove some nodes
    // auto generator = std::default_random_engine();
    // auto deathDistribution = std::uniform_int_distribution(0, 1);
    // auto removed = std::vector<bool>(nodes.size(), false);
    // std::generate(std::begin(removed), std::end(removed),
    //     [&generator, &deathDistribution](){ return deathDistribution(generator); });
    // for (auto& node : nodes)
    // {
    //     if (removed[node.id])
    //         quadtree.remove(&node);
    // }
    // // Quadtree
    // auto intersections1 = std::vector<std::vector<QuadNode*>>(nodes.size());
    // auto start2 = std::chrono::steady_clock::now();
    // for (const auto& node : nodes)
    // {
    //     if (!removed[node.id])
    //         intersections1[node.id] = quadtree.query(node.box);
    // }
    // auto duration2 = std::chrono::steady_clock::now() - start2;
    // auto duration1 = std::chrono::steady_clock::now() - start1;
    // std::cout << "quadtree: " << std::chrono::duration_cast<std::chrono::microseconds>(duration2).count() << "us" << '\n';
    // std::cout << "quadtree with creation: " << std::chrono::duration_cast<std::chrono::microseconds>(duration1).count() << "us" << '\n';
    // // Brute force
    // auto intersections2 = computeIntersections(nodes, removed);
    // // Check
    // //checkIntersections(intersections1[node.id], intersections2[node.id]);
    // // Find all intersections
    // auto intersections3 = quadtree.findAllIntersections();
    // std::cout << intersections3.size() << '\n';
    // std::cout << intersections2.size() << '\n';

 
    // std::cout << "BOOST???" << std::endl;
 
    // typedef std::istream_iterator<int> in;
    // std::cout << "Type in any number: ";

    // std::for_each(
    //     in(std::cin), in(), std::cout 
	// 			<< (boost::lambda::_1 * 10) 
	// 			<< "\nType in another number: " );

    // using namespace boost::lambda;
    // typedef std::istream_iterator<int> in;

    // std::for_each( in(std::cin), in(), std::cout << (_1 * 3) << "ss " );


    // std::vector<int> v{1, 3, 2};
    // std::for_each(v.begin(), v.end(), std::cout << boost::lambda::_1 << "\n");

    // auto glambda = [](auto a, auto&& b) { return a < b; };
    // bool b = glambda(3, 3.14); // ok

    // std::cout << "B: " << b << std::endl;
 
    // // generic lambda, operator() is a template with one parameter
    // auto vglambda = [](auto printer)
    // {
    //     return [=](auto&&... ts) // generic lambda, ts is a parameter pack
    //     { 
    //         printer(std::forward<decltype(ts)>(ts)...);
    //         return [=] { printer(ts...); }; // nullary lambda (takes no parameters)
    //     };
    // };
    // auto p = vglambda([](auto v1, auto v2, auto v3) { std::cout << v1 << v2 << v3; });
    // auto q = p(1, 'a', 3.14); // outputs 1a3.14
    // q();                      // outputs 1a3.14


    // boost::filesystem::path p1("Test");
    // std::cout << p1.filename() << std::endl;
    // int i;
    // std::cin >> i;
    // return 1;

     //////////////////////////////////////////////////////////////////////////////////////
     /////////////////////////////TINY MSG BOXES>>////////////////////////////////////////
     /////////////////////////////////////////////////////////////////////////////////////



//     int lIntValue;
// 	char const * lPassword;
// 	char const * lTheSaveFileName;
// 	char const * lTheOpenFileName;
// 	char const * lTheSelectFolderName;
// 	char const * lTheHexColor;
// 	char const * lWillBeGraphicMode;
// 	unsigned char lRgbColor[3];
// 	FILE * lIn;
// 	char lBuffer[1024];
// 	char const * lFilterPatterns[2] = { "*.txt", "*.text" };

// 	(void)argv; /*to silence stupid visual studio warning*/

// 	tinyfd_verbose = argc - 1;  /* default is 0 */
// 	tinyfd_silent = 1;  /* default is 1 */

// 	tinyfd_forceConsole = 0; /* default is 0 */
// 	tinyfd_assumeGraphicDisplay = 0; /* default is 0 */

// #ifdef _WIN32
// 	 tinyfd_winUtf8 = 1; /* default is 1 */
// /* On windows, you decide if char holds 1:UTF-8(default) or 0:MBCS */
// /* Windows is not ready to handle UTF-8 as many char functions like fopen() expect MBCS filenames.*/
// /* This hello.c file has been prepared, on windows, to convert the filenames from UTF-8 to UTF-16
//    and pass them passed to _wfopen() instead of fopen() */
//     std::cout << "-----------------------IS WIN 32!!!" << std::endl;

// #endif

// 	/*tinyfd_beep();*/

// 	lWillBeGraphicMode = tinyfd_inputBox("tinyfd_query", NULL, NULL);

// 	strcpy(lBuffer, "tinyfiledialogs\nv");
// 	strcat(lBuffer, tinyfd_version);
// 	if (lWillBeGraphicMode)
// 	{
// 		strcat(lBuffer, "\ngraphic mode: ");
// 	}
// 	else
// 	{
// 		strcat(lBuffer, "\nconsole mode: ");
// 	}
// 	strcat(lBuffer, tinyfd_response);
// 	tinyfd_messageBox("hello", lBuffer, "ok", "info", 0);

// 	tinyfd_notifyPopup("the title", "the message\n\tfrom outer-space", "info");

// 	if ( lWillBeGraphicMode && ! tinyfd_forceConsole )
// 	{
// #if 0
// 			lIntValue = tinyfd_messageBox("Hello World", "\
// graphic dialogs [Yes]\n\
// console mode [No]\n\
// quit [Cancel]",
// 				"yesnocancel", "question", 1);
// 			if (!lIntValue) return 1;
// 			tinyfd_forceConsole = (lIntValue == 2);
// #else
// 			lIntValue = tinyfd_messageBox("Hello World", "graphic dialogs [Yes] / console mode [No]", "yesno", "question", 1);
// 			tinyfd_forceConsole = ! lIntValue;
// #endif
// 	}

// 	lPassword = tinyfd_inputBox(
// 		"a password box", "your password will be revealed later", NULL);

// 	if (!lPassword) return 1;

// 	tinyfd_messageBox("your password as read", lPassword, "ok", "info", 1);

// 	lTheSaveFileName = tinyfd_saveFileDialog(
// 		"let us save this password",
// 		"passwordFile.txt",
// 		2,
// 		lFilterPatterns,
// 		NULL);

// 	if (! lTheSaveFileName)
// 	{
// 		tinyfd_messageBox(
// 			"Error",
// 			"Save file name is NULL",
// 			"ok",
// 			"error",
// 			1);
// 		return 1 ;
// 	}

// #ifdef _WIN32
// 	if (tinyfd_winUtf8)
// 		lIn = _wfopen(tinyfd_utf8to16(lTheSaveFileName), L"w"); /* the UTF-8 filename is converted to UTF-16 to open the file*/
// 	else
// #endif
// 	lIn = fopen(lTheSaveFileName, "w");

// 	if (!lIn)
// 	{
// 		tinyfd_messageBox(
// 			"Error",
// 			"Can not open this file in write mode",
// 			"ok",
// 			"error",
// 			1);
// 		return 1 ;
// 	}
// 	fputs(lPassword, lIn);
// 	fclose(lIn);

// 	lTheOpenFileName = tinyfd_openFileDialog(
// 		"let us read the password back",
// 		"",
// 		2,
// 		lFilterPatterns,
// 		NULL,
// 		0);

// 	if (! lTheOpenFileName)
// 	{
// 		tinyfd_messageBox(
// 			"Error",
// 			"Open file name is NULL",
// 			"ok",
// 			"error",
// 			0);
// 		return 1 ;
// 	}

// #ifdef _WIN32
// 	if (tinyfd_winUtf8)
// 		lIn = _wfopen(tinyfd_utf8to16(lTheOpenFileName), L"r"); /* the UTF-8 filename is converted to UTF-16 */
// 	else
// #endif
// 	lIn = fopen(lTheOpenFileName, "r");

// 	if (!lIn)
// 	{
// 		tinyfd_messageBox(
// 			"Error",
// 			"Can not open this file in read mode",
// 			"ok",
// 			"error",
// 			1);
// 		return(1);
// 	}

// 	lBuffer[0] = '\0';
// 	fgets(lBuffer, sizeof(lBuffer), lIn);
// 	fclose(lIn);

// 	tinyfd_messageBox("your password as it was saved", lBuffer, "ok", "info", 1);

// 	lTheSelectFolderName = tinyfd_selectFolderDialog(
// 		"let us just select a directory", NULL);

// 	if (!lTheSelectFolderName)
// 	{
// 		tinyfd_messageBox(
// 			"Error",
// 			"Select folder name is NULL",
// 			"ok",
// 			"error",
// 			1);
// 		return 1;
// 	}

// 	tinyfd_messageBox("The selected folder is", lTheSelectFolderName, "ok", "info", 1);

// 	lTheHexColor = tinyfd_colorChooser(
// 		"choose a nice color",
// 		"#FF0077",
// 		lRgbColor,
// 		lRgbColor);

// 	if (!lTheHexColor)
// 	{
// 		tinyfd_messageBox(
// 			"Error",
// 			"hexcolor is NULL",
// 			"ok",
// 			"error",
// 			1);
// 		return 1;
// 	}

// 	tinyfd_messageBox("The selected hexcolor is", lTheHexColor, "ok", "info", 1);

// 	tinyfd_messageBox("your read password was", lPassword, "ok", "info", 1);

// 	tinyfd_beep();

     //////////////////////////////////////////////////////////////////////////////////////
     //////////////////////////////////////////////////////////////////////////////////////
     /////////////////////////////////////////////////////////////////////////////////////

    GoBot g;
    return g.run();
}



//
//
//		screen.setBrainState(BrainStateStrings[brain.state]);
//
//               unsigned char green = (unsigned char) ((1 + sin(elapsed * 0.0001)) * 128);
//               unsigned char red = (unsigned char) ((1 + sin(elapsed * 0.0002)) * 128);
//               unsigned char blue = (unsigned char) ((1 + sin(elapsed * 0.0003)) * 128);
//               screen.lines.clear();
//               screen.points.clear();
//
//
//			if (brainViewIndex < (int)viewSensorIterator->second->nets.size() && brainViewIndex > -1) {
//
//				///DRAW NET
//				for (auto const& nodeRef : viewSensorIterator->second->nets[brainViewIndex]->nodes) {
//					Node *node = viewSensorIterator->second->nets[brainViewIndex]->nodes[nodeRef.first];
//					node->drawSelf(&screen, red, green, blue);
//				}
//
//				for (auto const& edgeRef : viewSensorIterator->second->nets[brainViewIndex]->edges) {
//					Edge *edge = viewSensorIterator->second->nets[brainViewIndex]->edges[edgeRef.first];
//					edge->drawSelf(&screen, red, green, blue);
//				}
//
//				if (viewSensorDataIterator != viewSensorIterator->second->nets[brainViewIndex]->NetOutputMap.end()) {
//					std::string inferedDataString = "";
//					if (viewSensorIterator->second->nets[brainViewIndex]->NetFactInferenceMap.count(viewSensorDataIterator->first) > 0) {
//						inferedDataString = viewSensorIterator->second->nets[brainViewIndex]->NetFactInferenceMap[viewSensorDataIterator->first]->data();
//					}
//
//					viewSensorIterator->second->nets[brainViewIndex]->drawNetOutput(&screen, brainViewIndex, viewSensorIterator->first, viewSensorDataIterator->first, inferedDataString);
//				}
//				else {
//					viewSensorIterator->second->nets[brainViewIndex]->drawNetOutput(&screen, brainViewIndex, viewSensorIterator->first, 0, "");
//				}
//
//			}
//
//
//
