
#define MAXM 5  //制作家具时需要木块的数量

/***********************************************************************
 以下变量均为猜测
 ***********************************************************************/
int len;  //购买时木块的长度
int loss;  // 锯子的宽度，即每次锯木材损失的木料宽度
int n;  // ？？？
int qlist[MAXM];  //制作家具时需要的木块长度数组
int mn;  // 需要木料数 ？？？


/************************************************************************
Perm函数参数定义:
list-->原始序列，存放每一个木块的编号
level->搜索到第几层
k-->list中搜索的起始位置
m-->list中搜索的最后位置
count->第几块木料，木料的数量
set->二维矩阵，存放每一块木料中放的是第几个木块，set[i][j]=1表示第i块木料可以锯成第j个木块
nlist->当前树中存放的list中的第几个木块，存放了所有可以组成当前木料的木块
 ***********************************************************************/

void Perm(int *list, int level, int k, int m, int count, int set[MAXM][MAXM], int nlist[MAXM])
{
    int i;
    int nset[MAXM][MAXM];
    int mlist[MAXM];
    int klist[MAXM];

    if (m == 0) {
        for (int l = k; l <= m; l++) {
            set[count - 1][list[l]] = 1;
        }
        //判断每一行中木块长度总和+每次废掉的木块是否超过一块木料的长度
        int flag = 0;
        for (int l= 0; l < count; l++) {
            int sum =0;
            for (int h = 0; h < n; h++) {
                if (set[l][h] == 1) {
                    sum += qlist[h] + loss;
                }   
            }
            if (sum > len + loss) {
                flag = 1;
                break;
            }
        }
        //如果所有的都满足，则当前木料的块数是一种选择
        if (flag == 0)
            mn = mn > count ? count : mn;
        return;
    } 

    //如果已经取完所有的木块，则返回上一层选取其他选的方法
    if (k > m) {

        return;
    }
    else {
        //对于每一块木料都有k-m种选方法，并深度遍历，每次取下一个木块，确保不重复取
        for(i = k; i <= m; i++) {

            //获取上一次在该树上选取的木块
            for (int l = 0; l < level; l++)
                klist[l] = nlist[l];
            //继续取下一层的木块
            klist[level] = list[i];

            //获取还剩余的木块
            int left = 0;
            for (int l = 0; l <= m; l++) {
                int s;
                for (int s = 0; s <= level; s++) {
                    if (list[l] == klist[s])
                        break;
                }
                if (s > level) {
                    mlist[left++] = list[l];
                }
            }

            //设置当前木料所选取的所有木块，nset[l][h]=1表示第l块木料可能锯成第h块木块
            for (int l = 0; l < MAXM; l++) {
                for (int h = 0; h < MAXM; h++) {
                    nset[l][h] = set[l][h];
                }
            }

            for (int l = 0; l <= level; l++) {
                nset[count-1][klist[l]] = 1;
            }

            //如果所有的木块均已取完，则是一种选择，求出满足条件的木料的数量，并计算最小的木料...
            left--;
            if (left < 0) {
                int flag = 0;
                for (int l = 0; l < count; l++) {
                    int sum = 0;
                    for (int h = 0; h < n; h++) {
                        if (nset[l][h] == 1) {
                            sum += qlist[h] + loss;
                        }
                    }
                    if (sum > len + loss) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                    mn = mn > count ? count : mn;
            }

            //将剩余木块作为下一个木料的所有选取方法的输入
            Perm(mlist, 0, 0, left, count+1, nset, klist);

            //取当前木料所对应的下一种木块的取法，每次取下一个木块，确保不重复取
            Perm( list, level+1, i+1, m, count, set, klist);
        }
    }
    return;
}