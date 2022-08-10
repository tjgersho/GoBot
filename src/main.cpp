//
//  main.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/27/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#include <iostream>
#include "Node.hpp"
#include "Sensor.hpp"
#include "iNet.hpp"
#include "Brain.hpp"
#include "Edge.hpp"
#include "MetaBrain.hpp"

#ifdef _WIN32 
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <chrono>
#include <thread>

#include "GOL.hpp"
#include <math.h>
#include "Screen.hpp"
#include <stdlib.h>
#include <time.h>
#include <map>
#include "SDLWindow.hpp"
#include <memory>
#include "GoBotWin.hpp"

#include <thread>
#include "GoBot.hpp"

#include "Label.hpp"


#include "QuadBox.hpp"
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include "QuadTree.hpp"

#undef main // This is needed because linker is confused by the main in the SDL library
 
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
 

class Song
{
public:

    Song(int track){
        _track = track;
    }
    void Play(){
         std::cout << "Playing Current Track: "<< _track << std::endl;
    }
    void PrintStr(std::string str){
        std::cout << str << std::endl;
    }
private:
    int _track;
 
};

class Album{
    public:
        std::vector<std::shared_ptr<Song>> songs;
        bool playing = false;

        void addTrack(std::shared_ptr<Song> s){
            songs.push_back(s);
        }

        void Play(int songIndex){
            playing = true;

            int currentTrack = songIndex;
            int fullAlbumPlayCount = 0;
            while(playing){
                
                songs[currentTrack]->Play();

                currentTrack++;

                if(currentTrack >= songs.size()){
                    currentTrack = 0;
                }

                if(fullAlbumPlayCount >= songs.size() ){
                    break;
                }

                fullAlbumPlayCount++;
            }
        }
};

class Studio {
    public:
        std::shared_ptr<Album> createAlbum(){
            auto a = std::make_shared<Album>();
            for(int i=0; i<5; i++){
                a->addTrack(std::make_shared<Song>(i));
            }
            return a;
        }
};

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




struct QuadNode
{
    QuadBox<float> box;
    std::size_t id;
};

std::vector<QuadNode> generateRandomNodes(std::size_t n)
{
    auto generator = std::default_random_engine();
    auto originDistribution = std::uniform_real_distribution(0.0f, 1.0f);
    auto sizeDistribution = std::uniform_real_distribution(0.0f, 0.01f);
    auto nodes = std::vector<QuadNode>(n);
    for (auto i = std::size_t(0); i < n; ++i)
    {
        nodes[i].box.left = originDistribution(generator);
        nodes[i].box.top = originDistribution(generator);
        nodes[i].box.width = std::min(1.0f - nodes[i].box.left, sizeDistribution(generator));
        nodes[i].box.height = std::min(1.0f - nodes[i].box.top, sizeDistribution(generator));
        nodes[i].id = i;
    }
    return nodes;
}

std::vector<std::pair<QuadNode*, QuadNode*>> computeIntersections(std::vector<QuadNode>& nodes, const std::vector<bool>& removed)
{
    auto intersections = std::vector<std::pair<QuadNode*, QuadNode*>>();
    for (auto i = std::size_t(0); i < nodes.size(); ++i)
    {
        if (removed.size() == 0 || !removed[i])
        {
            for (auto j = std::size_t(0); j < i; ++j)
            {
                if (removed.size() == 0 || !removed[j])
                {
                    if (nodes[i].box.intersects(nodes[j].box))
                        intersections.emplace_back(&nodes[i], &nodes[j]);
                }
            }
        }
    }
    return intersections;
}

void checkIntersections(std::vector<QuadNode*> nodes1, std::vector<QuadNode*> nodes2)
{
    assert(nodes1.size() == nodes2.size());
    std::sort(std::begin(nodes1), std::end(nodes1));
    std::sort(std::begin(nodes2), std::end(nodes2));
    for (auto i = std::size_t(0); i < nodes1.size(); ++i)
        assert(nodes1[i] == nodes2[i]);
}




int main(int argc, char**argv) {
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
