#include <cstdio>
#include <cstdlib>
#define p(a) int main(){printf(#a);system("pause");}
p(

FML:
    我把老的FML.cpp丢了。又要重新写了。FML 
A1858:
    第一次回忆线段树。写得又臭又长。而且指针都在乱指。最后的调出
    的一堆错误完全是笔误造成的。 FML
A2047:
    我设的最大值res初始化为200000000。少了一个0。 FML
A2588:
    第一次写超难主席树。主席树倒没写错……首先是边数组没考虑双向，
    开小了两倍。更可恶的是根的高度设小了1（设成了0），结果无限RE。
    大概总共用了4个多小时才做完。 FML
A1021:
    超难（对我来说）dp题。今天终于明白了在dp的时候用两个数组互相
    memcpy有多慢了（网上标程都用队列）。最后交的时候还CE了！我没
    把尝试测试memcpy速度时写的一个垃圾函数删掉。总共用了2个半小
    时。 FML 
A1066:
    第一次写网络流的题目。数组开小就交上去了。 FML
A1001:
    折腾够呛。原因是数组开小，又找不到哪里开小了。自己弄了个大数
    据才知道反向边数组也应该和正向边数组一样开大。 FML
A2245:
    第一次写费用流。最后结果要开long long但在哪里开我不知道。 FML
A1070:
    超强压线。时限1S，结果988MS测完。（很糟糕的费用流代码） FML 
A1041:
    好久没有写过这么混沌的代码了！反正就是向标程的数据靠。结果弄
    了一个晚上。 FML 
A1044:
    由于技术原因（不知道高速缓存对数组的作用）而导致大数据运行时
    间长。数组f[i][j]应时刻将i放在外层循环，不然效率很低。 FML
A1045:
    对maxint的错误估计让我不得不看数据才搞定这道题。原来设的是
    1999999999，应该到2147483647才能通过！ FML
A1300:
    C++的long double过坑。我以为它有4000多位（或者我还没发现怎么
    用），但现实是和double一样的位数。当然了，算法本身就不需要这
    么大的位数，应该一边做一边调位数。再当然了，大神根本不用我这
    么烂的做法，也就不存在这种问题。 FML 
A1502:
    越来越讨厌计算几何了！这题里我把最后一个圆锥的顶端坐标搞错了，
    下标n+1写作了n，还少乘了一个cot(alpha)，但样例竟然能在这种情
    况下对掉……最后只能看数据对标程。 FML
A1067:
    我知道我有生之年再也看不懂我写的这段代码。我也能理解在大数据
    数据的时候用errorlevel Debug的重要性了。
    我用小号交了一页，大号交了3次左右后才开始纠的错。调了半天，最
    后发现在某个数据点的第几千行出现了错误……这种错误出现了两次，
    原因是优先队列考虑取等这些细节问题的处理。另外，我用了3个map
    来完成。3个map！因为对代码彻底不报希望了。检测一个元素在map中
    是否存在我还用了<int，mnode>中struct mnode里的exist=true……
    感觉非常变扭……这段程序写了我3个半小时。应该是这几个月最坑我
    的一题了。 FML 
A1085：
    今天是悲剧的期末考试的完结。此题交时0msWA。怒看数据全对。怒对
    标程无异。刷了一页屏之后发现字符串数组长度设错了，变量设了
    char tc[6]，但读从tc[1]开始读5个字符。算上终止符应设成tc[7]…
    改了之后交，竟然直接对了……我的电脑为什么无法告诉我这里错掉
    了！！ FML
A1145:
    把排列函数C的界限min写作max。 FML
A1060:
    我以为是什么大难题通过率那么低，原来是官方数据错了……用了评论
    里的3条数据直接输出过的。 FML
A1058:
    做法非常多的奇葩题……我用的是Treap统计全局最小+线段树统计连续
    链表间最小。Treap的找比某个数小的最大数函数没有考虑出现两个相
    同的值的情况。 FML
A1031:
    后缀数组排序算法在n==1的时候在for(int tvar=1;tvar<n;tvar<<=1)
    里什么都没做。 FML 
A1251:
    我写的splay在downdata[下传标记]的时候如果不updata(更新结点)它
    的儿子就会爆炸。 FML 
    我又去看了一下题解…splay在下传标记的时候确实需要对孩子的某些
    统计数据进行更新。两个函数具体如下：
    updata:
        对于每个结点，能够保证在它上面的标记不下传之前，它的数据是
        正确的。 
        (1)在downdata后对子孙条件性地操作；
        (2)在rotate后连刷两次； 
        (3)在修改区间之后连刷三次。
    downdata:
        能够在树结构被破坏时及时下传标记，避免标记认错人。 
        (1)在splay的每一步连刷三次；
        (2)如果有翻转，findk的时候一直刷下去；
        (3)区间询问的时候对结点操作。 
A1050:
    第一次写块状链表的题目，结果还是突破10KB，和（别人写的较长的）
    splay一样长。在代码长度上和时间上均无法得到任何优势。 FML 
A1187:
    插头dp。同一个数组的压缩状态数和长度同时估计小。 FML
A1049:
    此题改了过多。最后一次改的原因是max值设成199999999，本来想设
    1999999999的……倒数第二次改的原因是最长上升子序列的最长长度
    直取了最后一个数字的dp值，没取整个数列的max值……瞄了N眼数据
    过的。 FML 
A1599:
    娱乐失败……色子随机投竟然会措…… FML
    PS:题解竟然都用dp……直接算又不会错…… FML 
A1043:
    计算几何水题，我把等价角的加减2PI写成了加减PI……而且一起写错
    了两个地方，就这样还过了前面几个样例…… FML 
    
A1563:
    初看有种很不祥的预感，后来果然被坑了……
    由于有超long long的情况，我把超范围的值都改成limit+1了。但由
    于写了单调决策的dp，这会导致判断决策最优性的时候乱七八糟……
    我又想了个办法把超范围的改long double，还是乱七八糟……
    最后看了标程，原来正确的做法是从dp开始清一色的long double，根
    本不需要管溢出问题……我根本没想到。 FML
    最后一次交的时候忘改%lld了。 FML 
A2038:
    第一次是按神牛题解中的某一种我认为比较简单的写法写的……结果
    熬夜写了150+行，越写越乱，最后爆炸了！！！改用zzk教我的神方法
    后AC，速度极快！ FML
A1196:
    大水题，输入的两种价格看反。 FML 
Z1195:
    能测的样例都过了，也考虑到所谓的AC程序都没考虑到的情况，结果连
    WA。放弃了。 FML 
A1030:
    第一次写AC自动机的题目，感觉太可怕了，交上去WA，连忙对拍。其实
    也就两个问题……1.局部未取模；2.输入读反了。 FML 
A1717:
    数组开大10倍就过了，不知道是数据范围的问题还是我写炸了。 FML 
A1862:
    这个程序弄了大概6个小时，弃坑了，一个非常奇怪的Treap+Hash后无
    限RE。无法查错，应学会放弃。 FML
    省选前我又用块状链表重新写了一遍这道题……这题时限只有5S，块状
    链表巨慢无比，最后用DevC++自带的分析优化了一下时间，把分块的大
    小改了一下，卡时过去了……但代码仍然巨长无比，这样的简单题也写
    了10KB…… FML
A1018:
    好苦恼的一题……拿着数据+标程还是搞了3个小时……我的n^1.5果断
    被nlogn虐爆……无限超时……最后加了一些恶心的优化，比如判这个
    询问和上个询问是否相同，结果这还写炸了……两个询问间夹修改也让
    它直接输出了……还有一个查了半天的错就是变量循环从0开始写成了1
    开始…… FML 
    本地cena测1.3s交上去2s多。 FML 
A1415:
    最近感觉极差……这题调了2个多小时，BFS求错导致两个点WA……要不
    是搞了个相似的标程我还不知道我还是在BFS这里写错了。
    要严谨地考虑BFS顺序的影响。 FML 
A3165:
    好神的暴力！把询问的时候遍历改成预处理就能A了！ FML 
A3107:
    第一次做法是错的。至少我还不知道怎么用贪心代替动归。 FML
    再做的时候WA了若干次……比如memset成无限大的时候不够大，题中要
    求n<=2^30，我当成了n<2^30。 FML
A3122:
    这题好猥琐，又对着数据调了半天……各种特判就不说了，其实这题题
    解里写的求逆元貌似是不需要的。（算法叫BabyStepGaintStep）。但
    我还是写得很渣而拿了Rank倒数第几。 FML 
A2433:
    如果同一个循环里并行做两件事，第一件失败了怎么可以直接continue
    呢。 FML 
A1226:
    这题写得太爆炸了！如果一个同学允许他后面的同学插队，那这个同学
    后面的SB同学不让他插队怎么办……这都是需要仔细考虑的……调了若
    干小时，配合zzk的程序。 FML 
     
)
