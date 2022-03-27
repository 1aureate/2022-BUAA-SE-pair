#pragma once
#include <iostream>
#include <unordered_set>
#include "InputsHandler.h"
#include "ParamHandler.h"
#include "stack"


class WordListHandler
{
private:
	ParamHandler paramHandler;
	std::unordered_map<char, std::list<Word>> head2words;
	std::unordered_map<char, std::list<Word>> tail2words;
	std::vector<Word> words;
	std::unordered_map<std::string, bool> visited;

	void dfsAllChain(Word& word, std::stack<std::string>& path, std::vector<std::stack<std::string>>& ans) {

		path.push(word.content);
		visited[word.content] = true;
		//std::cout << path.size() << std::endl;
		if (path.size() > 1) {
			ans.emplace_back(path);
		}

		for (auto& w : head2words[word.last]) {
			if (visited[word.content]) {
				continue;
			}
			dfsAllChain(w, path, ans);
		}
		visited[word.content] = false;
		path.pop();
	}

	void dfsLongest(Word& word, std::vector<std::string>& path, std::vector<std::string>& ans) {

		path.emplace_back(word.content);
		visited[word.content] = true;
		if (path.size() > ans.size() && path.size() > 1) {
			ans = path;
		}

		for (auto& w : head2words[word.last]) {
			if (visited[w.content]) {
				continue;
			}
			dfsLongest(w, path, ans);
		}
		visited[word.content] = false;
		path.pop_back();
	}

	void dfsLongestNoSameHead(Word& word, std::vector<std::string>& path, std::vector<std::string>& ans, std::vector<bool>& heads) {
		path.emplace_back(word.content);
		heads[word.first-'a'] = true;
		visited[word.content] = true;
		if (path.size() > ans.size()) {
			ans = path;
		}

		for (auto& w : head2words[word.last]) {
			if (heads[w.first-'a'] || visited[w.content]) {
				continue;
			}
			dfsLongestNoSameHead(w, path, ans, heads);
		}
		visited[word.content] = false;
		heads[word.first-'a'] = false;
		path.pop_back();
	}

	void dfsMaxAlphaNum(Word& word, std::vector<std::string>& path, int& pathSum, std::vector<std::string>& ans, int& sum) {
		path.emplace_back(word.content);
		visited[word.content] = true;
		pathSum += word.content.size();
		
		if (pathSum > sum) {
			ans = path;
			sum = pathSum;
		}

		for (auto& w : head2words[word.last]) {
			if (visited[w.content]) {
				continue;
			}
			dfsMaxAlphaNum(w, path, pathSum, ans, sum);
		}
		
		visited[word.content] = false;
		pathSum -= word.content.size();
		path.pop_back();
	}

public:

	WordListHandler(ParamHandler& _paramHandler, std::vector<Word> _words) {

		for (int i = 0; i < 26; i++) {
			head2words.emplace(i + 'a', std::list<Word>());
			tail2words.emplace(i + 'a', std::list<Word>());
		}
		
		words = _words;
		paramHandler = _paramHandler;

		for (auto w : words) {
			head2words[w.first].emplace_back(w);
			tail2words[w.last].emplace_back(w);
			visited[w.content] = false;
		}

		// TODO 检查数据的合法性
		
	}

	void handle() {
		std::cout << paramHandler.getType() << std::endl;
		switch (paramHandler.getType())
		{
		case Type::CHAIN_NUM:
			genChainsAll();
			break;
		case Type::CHAR_NUM:
			genMaxAlphaNumChains();
			break;
		case Type::WORD_NUM:
			if (!paramHandler.sameHead()) {
				genLongestChains();// -h -t / (-h -t)
			}
			else {
				genLongestChainsNoSameHead();
			}
			break;
		default:
			throw "illegal param type!";
			break;
		}
	}

	void genChainsAll() {
		std::vector<std::stack<std::string>> ans;
		std::stack<std::string> res;

		for (auto& w : words) {
			std::cout << w.content << std::endl;
			dfsAllChain(w, res, ans);
		}

		std::cout << ans.size() << std::endl;
		for (auto& st : ans) {
			std::string tmp = "";
			while (!st.empty()) {
				tmp = st.top() + " " + tmp;
				st.pop();
			}
			std::cout << tmp << std::endl;
		}
		
	}

	void genLongestChains() {
		std::vector<std::string> ans;
		std::vector<std::string> res;

		// 从words中筛选出以 ch1 开头的字母

		for (auto& w : words) {
			dfsLongest(w, res, ans); // 在路径中找出以 ch2 结尾的最长单词链
		}

		std::ofstream out("solution.txt", std::ios::out);

		for (auto& w : ans) {
			out << w << std::endl;
		}

		out.close();
	}
	void genLongestChainsHeadWithCh() {
		std::vector<std::string> ans;
		std::vector<std::string> res;

		for (auto& w : words) {
			dfsLongest(w, res, ans);
		}

		std::ofstream out("solution.txt", std::ios::out);

		for (auto& w : ans) {
			out << w << std::endl;
		}

		out.close();
	}

	void genLongestChainsTailWithCh() {


	}

	void genLogestChainsHeadWithCh1AndTailWithCh2() {


	}

	void genLongestChainsNoSameHead() {
		std::vector<bool> heads(26, false);
		std::vector<std::string> ans;
		std::vector<std::string> path;

		for (auto& w : words) {
			dfsLongestNoSameHead(w, path, ans, heads);
		}

		std::ofstream out("solution.txt", std::ios::out);

		for (auto& s : ans) {
			out << s << std::endl;
		}

		out.close();

	}

	void genMaxAlphaNumChains() {
		int sum = 0;
		int pathSum = 0;
		std::vector<std::string> ans;
		std::vector<std::string> path;


		// 筛选出以 ch1 为开头的单词进行遍历 
		for (auto& w : words) {
			dfsMaxAlphaNum(w, path, pathSum, ans, sum); //单词链中要求以 ch2 为结尾
		}

		std::ofstream out("solution.txt", std::ios::out);

		for (auto& s : ans) {
			out << s << std::endl;
		}

		out.close();
	}


	





};





