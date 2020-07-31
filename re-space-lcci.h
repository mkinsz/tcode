#ifndef RESPACELCCI_H
#define RESPACELCCI_H

/*
 *
 * 哦，不！你不小心把一个长篇文章中的空格、标点都删掉了，并且大写也弄成了小写。像句子"I reset the computer.
 * It still didn’t boot!"已经变成了"iresetthecomputeritstilldidntboot"。在处理标点符号和大小写之前，
 * 你得先把它断成词语。当然了，你有一本厚厚的词典dictionary，不过，有些词没在词典里。假设文章用sentence表示，
 * 设计一个算法，把文章断开，要求未识别的字符最少，返回未识别的字符数。
 *
 * 注意：本题相对原题稍作改动，只需返回未识别的字符数
 *
 * 来源：力扣（LeetCode）链接：https://leetcode-cn.com/problems/re-space-lcci
 *
 * 示例：
 * 输入：
 * dictionary = ["looked","just","like","her","brother"]
 * sentence = "jesslookedjustliketimherbrother"
 * 输出： 7
 * 解释： 断句后为"jess looked just like tim her brother"，共7个未识别字符。
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Trie {
    Trie* next[26] = {nullptr};
    bool isEnd = false;

    void insert(std::string s) {
        Trie* curPos = this;
        int len = s.length();

        for(auto i = len - 1; i >= 0; --i) {
            int t = s[i] - 'a';

            if(!curPos->next[t])
                curPos->next[t] = new Trie();

            curPos = curPos->next[t];
        }

        curPos->isEnd = true;
    }

    int find(std::string s) {
        return 0;
    }
};

struct Solution {
    using LL = long long;
    static constexpr LL BASE = 41;

    int respace(std::vector<std::string>& dictionary, std::string sentence) {
        int n = sentence.length(), inf = 0x3f3f3f3f;

        Trie* root = new Trie();
        for(auto& word: dictionary)
            root->insert(word);

        std::vector<int> dp(n+1, inf);
        dp[0] = 0;
        for(int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1] + 1;

            Trie* curPos = root;
            for(int j = i; j >= 1; --j) {
                int t = sentence[j - 1] - 'a';
                if(!curPos->next[t]) break;
                else if(curPos->next[t]->isEnd) dp[i] = std::min(dp[i], dp[j - 1]);
                if(!dp[i]) break;

                curPos = curPos->next[t];
            }
        }
        return dp[n];
    }
};

// 测试代码
//int main() {
//    std::vector<std::string> dictionary{"looked","just","like","her","brother"};
//    std::string sentence = "jesslookedjustliketimherbrother";

//    Solution sl;
//    int n = sl.respace(dictionary, sentence);
//    std::cout << n << std::endl;

//    return 0;
//}


#endif // RESPACELCCI_H
