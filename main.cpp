#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <string>

std::string replaceBadWords(std::vector<std::string>&insults, std::string toReplace);
void saveToFile(std::ofstream& badWordsJournal, std::string badWord);

int main(int argc, char* argv[])
{
    std::string word;
    std::vector<std::string>insults;
    std::cout << "==Menu==\n1. Dodanie przeklenstwa\n2. Zobaczenie czy program dziala\n3. Exit";
    int answ = _getch();
    if (answ == 49)
    {
        std::ofstream insult;
        std::cout << "\nPodaj przeklenstwa, do dodania, kazde po enterze: ";
        do
        {
            std::getline(std::cin, word);
            if (word.empty() == false)
                saveToFile(insult, word);
            else
                continue;
        } while (!word.empty());
        insult.close();
    }
    else if (answ == 50)
    {
        std::ifstream insult;
        std::string s1, str, s2;
        insult.open("insults.txt");
        if (insult)
        {
            std::cout << "\nPodaj zdanie do testowania: ";
            while (std::cin.peek() != '\n')
            {
                std::cin >> s1;
                s2 += s1 + " ";
            }
            while (!insult.eof())
            {
                insult >> str;
                insults.push_back(str);
            }
            std::cout << replaceBadWords(insults, s2);
        }
        else
            std::cout << "\nNie znaleziono slownika!";
        insult.close();
    }
    else
    {
        std::cout << "\nWybrano zly przycisk!";
    }
}

std::string replaceBadWords(std::vector<std::string>&insults, std::string toReplace)
{
    for (int i = 0; i < insults.size(); i++)
    {
        if (toReplace.find(insults[i]) != std::string::npos)
        {
            auto foundIndex = toReplace.find(insults[i]);
            std::string temp = insults[i];
            for (int i = 0; i < temp.length(); i++)
                temp[i] = '*';
            toReplace.replace(foundIndex, temp.length(), temp);
        }
        else
            continue;
    }
    return toReplace;
}

void saveToFile(std::ofstream& badWordsJournal, std::string badWord)
{
        badWordsJournal.open("insults.txt", std::ios::app);
        badWord += "\n";
        badWordsJournal << badWord;
        badWordsJournal.close();
}