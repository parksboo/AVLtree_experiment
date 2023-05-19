자료구조의 활용 : 자료 검색 효울성 높이기 (AVL tree)
============================================



+ (해당자료는 chatGPT이 일부분 활용되어 만들어졌음을 알립니다.)

# principle of implementation

AVL tree의 구현은 크게 Binary Search Tree와 동일한 부분과 height를 활용한 rotation 부분으로 나눌 수 있다. 이 중 구현 난이도가 상대적으로 높은 후자의 구현에 중점을 둔 해설이다. 

## code


+ function insertNode 중 일부
<pre>
<code>
int BF = getBalance(node);

    // balance 재조정

    // Left Left Case
    if (BF > 1 && code < node->left->code)
        return rightRotate(node);

    // Left Right Case
    if (BF > 1 && code > node->left->code)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Right Case
    if (BF < -1 && code > node->right->code)
        return leftRotate(node);

    // Right Left Case
    if (BF < -1 && code < node->right->code)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
retrurn node;
</code>
</pre>
해당 코드는 BST에서와 동일한 과정으로 insert가 이루어진 후 tree의 balance를 조정하는 부분이며 각각의 node는 node의 level을 반영하고 있는 height라는 멤버를 가지고있다. getBalance는 left child의 height - right child의 height를 계산하여 반환하는 함수이다. 해당 함수를 통해 나온 결과를 BF(balance factor)로 정의하고 BF의 값이 -1, 0, 1 이외에 다른 값이 나오는 경우 balance가 깨진 것으로 balance 재조정 과정을 거치게 된다. balance 재조정은 Left(L), Right(R)로 LL, LR, RR, RL 4가지 case로 나누어서 진행하는데 BF > 1 이고 left child의 code보다 추가한 code가 작은 경우를 LL case, BF > 1 이고 left child의 code보다 추가한 code가 큰 경우를 LR case라고 한다. 이러한 두케이스의 경우 left child의 heiht 변화에 의해 balance가 깨진 것이며 left child와 추가된 node와의 크기 비교를 통해 left child의 left에서 불균형이 비롯된 것인지 right에서 불균형이 비롯된 것인지를 알아낸다. 이렇게 알아낸 정보를 바탕으로 나눠진 case에 따라 균형을 맞출 수 있도록 반대 방향으로 rotation을 진행하는데 아래는 rotation을 실행하는 함수이다. 
<pre>
<code>
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}
</code>
</pre>
right/left rotation은 같은 원리로 이루어지므로 right rotation의 code를 예시로 가져왔다. y는 현재 기준점이 되는 노드이고 x는 y의 left child로 새롭게 기준점으로 바꾸고 싶은 노드이다. x는 y보다 작은 수 이므로 y를 내리며 x의 right child로 보내고 y보다 작은 수인 본래 x의 right child를 x의 새로운 right child가 된 y의 left child로 보낸다. 이를 통해 가장 root로 볼 수 있는 위치에 y의 left child 였던 x가 오게 되는 것이 right rotation이다. 
다시 LL / LR case로 돌아가 LL 의 경우 rotation을 통해 현재 root가 들어가는 위치가 right이므로 그냥 right rotation만으로 균형을 찾을 수 있다. 하지만 LR case는 left child의 right child가 불균형의 원인이었기 때문에 이를 해소하기 위해 반드시 left rotation(left child) 후에 right rotation을 실시해야한다. RR / RL case 역시 동일한 원리로 작동한다.

# 프로그램 실행

## input file

input file은 반드시 csv file이어야하며 UTF-8로 인코딩 되어야합니다. 또한 실행 환경 또한 이에 맞춰 UTF-8을 따라야만 한글이 정상적으로 출력됩니다.
test를 위한 input file은 dataset 디렉토리에 위치해있으며 더미 데이터인 exdata.csv, naver finance에서 웹크롤링을 통해 얻은 실제 KOSPI/KOSDAQ data인 tdata.csv로 이루어져있습니다.

+ 2023/04/13 KOSDAQ/KOSPI 기업의 기업코드/이름/시총/주가를 담고있는 tdata.csv 
+ mkdata.py file에 의해 만들어지는 실험을 위한 더미 데이터 exdata.csv


## 프로그램 구성

실험을 구현하는 코드는 모두 c language로 구현이 되어있으며 makefile을 통해 컴파일할 수 있습니다.

+ avlTree.c : AVL tree의 구현 및 search algorithm
+ csv.c : input으로 csv file을 받아오고 해당 자료를 array 형태로 저장하는 것에 사용되는 함수 및 search algorithm
+ main.c : 만들어진 모듈들을 활용하려 실험을 구현하는 main 함수


## 실행

실험의 실행은 test1.sh와 test2.sh를 통해 이루어지며 해당 쉘 스크립트를 통해 실험의 반복 수행 및 make를 포함한 실험에 필요한 전 과정을 하나의 cmd로 실행할 수 있도록 하였습니다.

+ test1.sh : 더미 데이터를 활용하여 data size별로 각각의 알고리즘을 수행, 결과를 result 디렉토리에 csv file로 저장
+ test2.sh : KOSDAQ/KOSPI 데이터를 활용하여 각각의 알고리즘을 반복 수행, 결과를 result 디렉토리에 csv file로 저장


# 분석 및 시각화

데이터의 분석 및 시각화는 Rstudio를 활용하였으며 visualization 디렉토리에 해당 코드가 저장되어있습니다.

+ (해당자료는 chatGPT이 일부분 활용되어 만들어졌음을 알립니다.)