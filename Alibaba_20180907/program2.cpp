#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <stack>

using namespace std;


// 在基于自然语言的人机交互系统中，通常会定义一些语义模板来训练NLU（自然语言理解）模型，
// 比如下面的模板可以支持用户通过语音控制机器播放音乐：
/*
 1.放几首@{singer}的歌

2.播放一首@{singer}的歌

3.来一曲@{singer}的歌曲

4.来首@{singer}的音乐

5.来个@{singer}的流行音乐

 其中"@{singer}"是一个参数，代表歌手，
 比如第一个模板可以匹配这样的用户query：“放几首刘德华的歌“。
 可以看到，同样是放歌，有很多种不同但相似的说法，但把他们一条一条单独列出来，编辑的成本会比较高，
 而且会漏掉一些说法，不严谨。实际上，上面的5个模板，可以用下面的语义模板表达式来表示：

<[播]放|来>[一|几]<首|曲|个>@{singer}的<歌[曲]|[流行]音乐>

其中包含中括号（“[]”）、尖括号（“<>”）和竖线（“|”）三种元素：
    1.中括号代表其中的内容是可选的，比如“歌[曲]”，能匹配“歌”和“歌曲”；
    2.尖括号代表其中的内容是必选的，比如“<播>放”，能匹配“播放”；
    3.括号是可以嵌套的；
    4.竖线代表“或”的关系，即竖线分隔的内容是可替换的，比如“<播放|来首>歌曲”,
    能匹配“播放歌曲”和“来首歌曲”,再如“[播放|来首]歌曲”,能匹配”播放歌曲“，
    ”来首歌曲“和”歌曲“（因为中括号里面是可选的，所以可以匹配”歌曲“）；

    5.竖线在其所属的括号内，优先级大于括号中的其他括号，比如” <[播]放|来>首歌曲”，
        能匹配“播放首歌曲“，“放首歌曲“和”来首歌曲“；
    6. 竖线可以脱离括号独立存在，比如”在哪里|哪里有”，可以匹配“在哪里”和“哪里有”;

 那么，给一个上述的语义模板表达式和用户的query，你能判断用户的query是否能匹配这个表达式吗？


 输入:
    输入数据包含两行，
    第一行，上述格式的语义模板表达式
    第二行，用户的自然语言指令（即：用户query）
输出:
    当前query是否匹配当前语义模板表达式。匹配，则输出1，否则输出0.
    输入范例:
        <[播]放|来>[一|几]<首|曲|个>@{singer}的<歌[曲]|[流行]音乐>
        来几首@{singer}的流行歌曲
输出范例:
        0

在哪里|哪里有

哪里有
 *
 *
 *
 */


set<char> symbolSet = {
        '<',
        '>',
        '[',
        ']',
        '|',
        '@',
        '{',
        '}'
};

// <[播]放|来>[一|几]<首|曲|个>@{singer}的<歌[曲]|[流行]音乐>
bool tryMatch(string &NLU, string &generationStr, string &query, int index) {

    if (index >= NLU.size())
        return false;

    if (generationStr == query)
        return true;

    bool res = false;

    // 符号
    if (NLU[index] == '<') {
        //  找到 < > 的位置
        int start = index;
        int end = start + 1;
        while (NLU[end] != '>')
            end += 1;

        // 这个区间必须要
    } else if (NLU[index] == '[') {
        //  找到 [ ] 的位置
        int start = index;
        int end = start + 1;
        while (NLU[end] != ']')
            end += 1;
    } else if (NLU[index] == '|') {
        //  找到  |  的位置
        int start = index - 1;
        while (start >= 0 && symbolSet.find(NLU[start]) == symbolSet.end())
            index -= 1;

        if (start < 0)
            start = 0;

        int end = index + 1;
        while (end < NLU.size() && symbolSet.find(NLU[end]) == symbolSet.end())
            end += 1;

        if (end >= NLU.size())
            end = NLU.size() - 1;

    } else if (NLU[index] == '@') {
        //  找到 @ { }  的位置
        int start = index;
        int end = start + 1;
        while (NLU[end] != '}')
            end += 1;

        // 必须匹配
    }

    return res;
}


int main() {

    string NLU;

    string query;

    cin >> NLU;

    cin >> query;


    string generationStr = "";
    int index = 0;
    bool res = tryMatch(NLU, generationStr, query, index);


    cout << (int) res << endl;


    return 0;
}