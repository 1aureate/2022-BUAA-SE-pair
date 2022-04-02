#pragma once
#include <iostream>
#include <unordered_set>
#include "InputsHandler.h"
#include "ParamHandler.h"
#include "stack"
#include <algorithm>
#include <unordered_set>


class WordListHandler
{
private:
	ParamHandler paramHandler;
	std::unordered_map<char, std::list<Word>> head2words;
	std::unordered_map<char, std::list<Word>> tail2words;
	std::vector<Word> words;
	std::unordered_map<std::string, bool> visited;
	std::vector<int> chVis;



	std::vector<Word> samplePoints(char ch) {
		if (ch == '*') {
			return words;
		}
		else {
			std::vector<Word> ans;
			ans.assign(head2words[ch].begin(), head2words[ch].end());
			return ans;
		}
	}

	void dfsCheck(Word& word, std::vector<std::string>& path) {
		path.emplace_back(word.content);
		visited[word.content] = true;

		if (path.front().front() == path.back().back() && path.size() > 1) {
			std::string tmp = "";
			for (auto& s : path) {
				tmp = tmp + " " + s;
			}
			throw ExistsLoopException("there is a circle in the data: " + tmp);
		}

		for (auto& w : head2words[word.last]) {
			if (visited[w.content]) {
				continue;
			}
			dfsCheck(w, path);
		}
		visited[word.content] = false;
		path.pop_back();
	}

	void dfsAllChain(Word& word, std::vector<std::string>& path, std::vector<std::vector<std::string>>& ans) {

		path.emplace_back(word.content);
		visited[word.content] = true;
		if (path.size() > 1) {
			ans.emplace_back(path);
		}

		for (auto& w : head2words[word.last]) {
			if (visited[w.content]) {
				continue;
			}
			dfsAllChain(w, path, ans);
		}
		visited[word.content] = false;
		path.pop_back();
	}

	// -w -h -r  -t
	void dfsLongest(Word& word, std::vector<std::string>& path, std::vector<std::string>& ans, char ch) {

		path.emplace_back(word.content);
		visited[word.content] = true;

		if (path.size() > ans.size() && path.size() > 1 && (word.last == ch || ch == '*')) {
			ans = path;
		}

		for (auto& w : head2words[word.last]) {
			if (visited[w.content]) {
				continue;
			}
			dfsLongest(w, path, ans, ch);
		}
		visited[word.content] = false;
		path.pop_back();
	}

	void dfsLongestNoSameHead(Word& word, std::vector<std::string>& path, std::vector<std::string>& ans, std::vector<bool>& heads) {
		path.emplace_back(word.content);
		heads[word.first - 'a'] = true;
		visited[word.content] = true;
		if (path.size() > ans.size()) {
			ans = path;
		}

		for (auto& w : head2words[word.last]) {
			if (heads[w.first - 'a'] || visited[w.content]) {
				continue;
			}
			dfsLongestNoSameHead(w, path, ans, heads);
		}
		visited[word.content] = false;
		heads[word.first - 'a'] = false;
		path.pop_back();
	}

	void dfsMaxAlphaNum(Word& word, std::vector<std::string>& path, int& pathSum, std::vector<std::string>& ans, int& sum, char ch) {
		path.emplace_back(word.content);
		visited[word.content] = true;
		pathSum += word.content.size();

		if (pathSum > sum && (ch == '*' || word.last == ch)) {
			ans = path;
			sum = pathSum;
		}

		for (auto& w : head2words[word.last]) {
			if (visited[w.content]) {
				continue;
			}
			dfsMaxAlphaNum(w, path, pathSum, ans, sum, ch);
		}

		visited[word.content] = false;
		pathSum -= word.content.size();
		path.pop_back();
	}

	void getRidOfDuplication(std::vector<Word>& _words) {
		std::unordered_set<std::string> s;
		std::vector<Word> new_words;
		for (auto& w : _words) {
			if (s.find(w.content) == s.end()) {
				new_words.emplace_back(w);
				s.emplace(w.content);
			}
		}
		_words = new_words;
	}

public:

	WordListHandler(ParamHandler& _paramHandler, std::vector<Word> _words) {
		getRidOfDuplication(_words);

		std::unordered_set<std::string> s;
		for (int i = 0; i < 26; i++) {
			head2words.emplace(i + 'a', std::list<Word>());
			tail2words.emplace(i + 'a', std::list<Word>());
			chVis.emplace_back(false);
		}

		words = _words;
		paramHandler = _paramHandler;

		for (auto& w : words) {
			if (s.find(w.content) == s.end()) {
				s.emplace(w.content);
			}
			else {
				continue;
			}
			head2words[w.first].emplace_back(w);
			tail2words[w.last].emplace_back(w);
			visited[w.content] = false;
		}
		if (!paramHandler.allowCircle()) {
			std::vector<std::string> path;
			for (auto& w : words) {
				dfsCheck(w, path);
			}
		}
	}

	std::vector<std::string> handle() {
		switch (paramHandler.getType())
		{
		case Type::CHAIN_NUM:
			// -n
			return genChainsAll();
			break;
		case Type::CHAR_NUM: {
			// -c
			char ch1 = (paramHandler.specializedHead() == 0) ? '*' : paramHandler.specializedHead();
			char ch2 = (paramHandler.specializedTail() == 0) ? '*' : paramHandler.specializedTail();
			// std::cout << ch1 << " - " << ch2 << std::endl; // What the fuck is this?
			return genMaxAlphaNumChains(ch1, ch2);
			break;
		}

		case Type::WORD_NUM: {
			// -w
			if (!paramHandler.noSameHead()) {
				char ch1 = (paramHandler.specializedHead() == 0) ? '*' : paramHandler.specializedHead();
				char ch2 = (paramHandler.specializedTail() == 0) ? '*' : paramHandler.specializedTail();
				// std::cout << ch1 << " - " << ch2 << std::endl;
				return genLongestChains(ch1, ch2);
			}
			else {
				// -m
				return genLongestChainsNoSameHead();
			}
			break;
		}
		default:
			throw ParamException("illegal param type!");
			break;
		}
	}

	std::vector<std::string> genChainsAll() {
		std::vector<std::vector<std::string>> ans;
		std::vector<std::string> res;

		std::vector<std::string> real_ans;


		for (auto& w : words) {
			dfsAllChain(w, res, ans);
		}

		std::cout << ans.size() << std::endl;
		for (auto& st : ans) {
			std::string tmp = "";
			for (auto& p : st) {
				tmp = tmp + " " + p;
			}
			real_ans.emplace_back(tmp);
		}
		return real_ans;
	}

	std::vector<std::string> genLongestChains(char ch1, char ch2) {
		std::vector<std::string> ans;
		std::vector<std::string> res;
		// 从words中筛选出以 ch1 开头的字母
		std::vector<Word> sample = samplePoints(ch1);

		for (auto& w : sample) {
			dfsLongest(w, res, ans, ch2); // 在路径中找出以 ch2 结尾的最长单词链	  
		}

		return ans;
	}

	std::vector<std::string> genLongestChainsNoSameHead() {
		std::vector<bool> heads(26, false);
		std::vector<std::string> ans;
		std::vector<std::string> path;

		for (auto& w : words) {
			dfsLongestNoSameHead(w, path, ans, heads);
		}

		/*std::ofstream out("solution.txt", std::ios::out);

		for (auto& s : ans) {
			out << s << std::endl;
		}

		out.close();*/
		return ans;
	}

	std::vector<std::string> genMaxAlphaNumChains(char ch1, char ch2) {
		int sum = 0;
		int pathSum = 0;
		std::vector<std::string> ans;
		std::vector<std::string> path;

		// 筛选出以 ch1 为开头的单词进行遍历 
		std::vector<Word> sample = samplePoints(ch1);

		for (auto& w : sample) {
			dfsMaxAlphaNum(w, path, pathSum, ans, sum, ch2); //单词链中要求以 ch2 为结尾
		}

		/*std::ofstream out("solution.txt", std::ios::out);

		for (auto& s : ans) {
			out << s << std::endl;
		}

		out.close();*/
		return ans;
	}








};





