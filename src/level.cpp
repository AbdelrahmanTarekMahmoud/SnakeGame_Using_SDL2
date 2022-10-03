#include "level.h"

   Level::Level()
   {
    setDifficulty();
    readBorders();
   }
   void Level::setDifficulty()
   {
    std::cout<<"Please Enter The Difficulty you want : "<<std::endl;
    std::cout<<"Easy press (e)" <<std::endl;
    std::cout<<"Medium press (m)" <<std::endl;
    std::cout<<"Hard press (h)" <<std::endl;
    std::cout<<"SuperSaiyan press (s)" <<std::endl;
    char input;
    std::cin>>input;
    std::string Path;
    if(input == 'e' || input == 'E')
    {
      difficulty = Difficulty::kEasy;
    }
    else if(input == 'm' || input == 'M')
    {
      difficulty = Difficulty::kMedium; 
    }
    else if(input == 'h' || input == 'H')
    {
      difficulty = Difficulty::kHard;
    }
    else if(input == 's' || input == 'S')
    {
      difficulty = Difficulty::kSupersaiyan;
    }
    else
    {
      std::cout<<"Error input Please try again" << std::endl;
      setDifficulty();
    }
   }

   Level::Difficulty Level::getDifficulty()
   {
    return difficulty;
   }

   void  Level::readBorders()
   {
    std::string Path;

    if(difficulty == Difficulty::kEasy)
    {
      Path ="EASY.txt";
    }
    else if(difficulty == Difficulty::kMedium)
    {
      Path ="MEDIUM.txt";
    }
    else if(difficulty == Difficulty::kHard)
    {
      Path ="HARD.txt";
    }
    else if(difficulty == Difficulty::kSupersaiyan)
    {
      Path ="supersaiyan.txt";
    }
    std::cout<<"The Selected Path is : " <<Path<<std::endl;


    SDL_Point Dummy;
    int row = -1;
    int col = -1;

    std::ifstream MyFile;
    MyFile.open("../Levels/" + Path);

    if(MyFile)
    {
        std::cout << "File stream created successfully!" <<std::endl;
        std::string line;
        while(getline(MyFile , line))
        {
            row++;
            std::istringstream MyString(line);
            int n;
            char c;
            while(MyString>>n>>c && c==',')
            {
                col++;
                if(n == 1)
                {
                    Dummy.x = row;
                    Dummy.y = col;
                    Borders.push_back(Dummy);
                }
            }
            col = -1;
        }
    }
    else
    {
        std::cerr<<"File Didnt open Succesfully :(" << std::endl; 
    }
    
   }

   std::vector<SDL_Point>  Level::getBorders()
   {
     return Borders;
   }
  // Inefficient method to check if cell is occupied by Border.
   bool Level::BorderCell(int &x, int &y)
   {
    for (auto const &item : Borders) 
    {
      if (x == item.x && y == item.y) 
       {
       return true;
       }
    }
     return false;
   }

