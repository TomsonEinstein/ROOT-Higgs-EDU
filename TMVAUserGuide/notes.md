# TMVA User Guide Notes

Contributors:周飞扬，陈瑞琪

**This manual introduces the TMVA Factory and Reader interfaces, and describes design and implementation of the MVA methods.**

It is not the aim here to provide a general introduction to MVA
techniques.如果想看，就去看Reference.
## 内容
 - The document begins with a quick TMVA start reference in Sec. 2
 - and provides a more complete introduction to the TMVA design and its functionality for both, classification and regression analyses in Sec. 3.
 - Data preprocessing such as the transformation of input variables and event sorting are discussed in Sec. 4. 
 - In Sec. 5, we describe the techniques used to estimate probability density functions from the training data. 
 - Section 6 introduces optimisation and fitting tools commonly used by the methods.
 - All the TMVA methods including their configurations and tuning options are described in Secs. 8.1–8.14.
 -  Guidance on which MVA method to use for varying problems and input conditions is given in Sec. 11. 
 -  An overall summary of the implementation status of all TMVA methods is provided in Sec. 12.

**帮助文档**
Several help sources exist for TMVA (all web address given below are also linked from the TMVA home page http://tmva.sourceforge.net).
 - TMVA tutorial: https://twiki.cern.ch/twiki/bin/view/TMVA.
 - The help message is printed when the option ”H” is added to the configuration string while booking the method (switch off by setting ”!H”).
 - The web address of this Users Guide: https://root.cern/download/doc/tmva/TMVAUsersGuide.pdf.
 - Source code: https://github.com/root-project/root/tree/master/tmva.
 - Please ask questions and/or report problems in the ROOT forum https://root-forum.cern.ch.

## Chapter 1 Introductions TMVA是什么，有什么，能干什么
 - TMVA use “supervised learnning” algorithms **监督学习**
 - 过程
   - classification（**分类**）:discribes a decision boundary
   - regression（**回归**）:define the target value
 - 主要的**MVA techniques**
   - 矩形切割优化
   - 射影似然估计
   - 多维似然估计
   - 线性和非线性判别分析
   - 人工神经网络
   - 支持向量机
   - 增加/袋装决策树
   - 通过规则集成的预测学习
   - 一个通用的增强分类器，允许增强上面任何一个分类器
   - 一个通用类别分类器，允许一个人分割训练数据为不相交的类别与独立的mva。
   - 一些辅助工具:拟合和变换
 - **提供训练、测试和表现评估算法，以及可视化工具**
 - TMVA **Factory** Class
   - 管理用户和TMVA分析步骤的交互
   - 进行预分析和预处理，来得到基本的变量性质，然后用作分类
   - 计算并显示输入变量的线性相关系数，对于回归，还给出了非线性相关度量。
   - 得出一个初步排名，后来被算法特定的变量排名所取代。
   - 对于分类问题，变量可以线性变换（每个 MVA 方法单独）成非相关变量空间，投影到它们的主成分上，或转换为归一化的高斯形状。变换也可以任意连接。
 - 提供分析可视化，用来比较分类的表现
 - 是一个独立的可执行脚本
 - TMVA **Reader** Class
   - 读取并解释权重文件
   - 有些方法可以使用Response Class，包含权重文件的编码信息，于是就不要权重文件了
 - **We stress however that, to solve a concrete problem, all methods require at least some specific tuning to deploy their maximum classification or regression capabilities** 要调整！！！不要生搬硬套

## Chapter 2 TMVA Quick Start
### TMVA namespace: 
TMVA::
### Example jobs
 - The training examples are TMVAClassification.C, TMVAMulticlass.C and TMVARegression.C, 
 - the application examples are TMVAClassificationApplication.C, TMVAMulticlassApplication.C and TMVARegressionApplication.C
 - Additionally TMVACrossValidation.C shows how cross validation is performed in TMVA, and examples in $ROOTSYS/tutorials/tmva/test/keras shows how to use TMVA with keras.
```cpp
> root -l $ROOTSYS/tutorials/tmva/TMVAClassification.C
> echo "Unix.*.Root.MacroPath: $ROOTSYS/tutorials/tmva" >> ~/.rootrc
//不建议使用，它会将macropath改成这个不常用的位置
> root -l TMVAClassification.C
//选择你要使用的MVA方法
> root -l '$ROOTSYS/tutorials/tmva/TMVAClassification.C("Fisher","BDT")'
```
标准化输出内容：
 - 输入变量的线性相关矩阵
 - 相关系数
 - 输入变量和回归目标的互信息
 - 变量排名
 - MVA配置概述
 - PDF 的拟合优度评估（如果需要）、各种 MVA 方法之间的信号和背景（或回归目标）相关性、决策重叠、基准背景拒绝率（分类）或与目标的偏差（回归）信号效率
 - 与其他性能估计器一样。 训练结果与独立测试结果的比较样本提供过度训练验证。
### 展示结果 GUI
```cpp
> root -l -e 'TMVA::TMVAGui("path/to/tmva/output/file.root")'
> root -l -e 'TMVA::TMVAMultiClassGui("path/to/tmva/output/file.root")'
> root -l -e 'TMVA::TMVARegGui("path/to/tmva/output/file.root")'
//也可以在训练代码中加上一行
if (not gROOT->IsBatch()) {
TMVA::TMVAGui("path/to/tmva/output/file.root");
}
```
由这些macros产生的图的示例在图 1-2 中给出。 4-6 用于分类问题。根据我们的示例，信号和背景的输入变量的分布如图 3 所示。量化输入变量之间的相关性很有用。 这些以散点图的形式绘制，其中两个输入变量的叠加轮廓图 4（左上）。 正如将在 Sec.4 中讨论的那样。TMVA允许执行线性去相关在 MVA 训练之前转换输入变量（仅用于分类）。 结果这种去相关的关系如图 4 的右上角图所示。下图显示了所有输入变量之间的线性相关系数，用于信号和背景训练分类示例的样本。
图 5 显示了基于信号和背景事件的几个分类器输出分布测试样品。 按照 TMVA 约定，信号（背景）事件在大（小）处累积分类器输出值。 因此，减少输出并保留 y 大于的事件切割要求选择效率和纯度分别降低的信号样本并随着截断值的增加而增加。 背景抑制与信号之间的最终关系对于示例macro中使用的所有分类器，效率如图 6 所示。 这个情节属于**接收器操作特性 (ROC) 图**的类别，在其标准中表格显示了不同可能切点的真阳性率与假阳性率的假设检验。
对于多类分类，相应的 GUI 显示在图 2（左）中。二分 GUI 存在一些不同之处。 ROC 空间是 C(C-1) 维的，即正比与类数的平方。 可视化这个潜在的高维空间随着维数的增加变得棘手。为了仍然深入了解分类器的性能，TMVA 提供了 ROC 表面到 2D 的两个投影。 在 1 对 其他 中，C 地块生成，其中每个类依次被认为是信号，而其余的被认为是背景。 在 1 对 1 中，在考虑每对类的情况下生成 C(C-1)图。不属于这两个类别中的任何一个的事件在计算该 ROC 时将被忽略曲线。 图 2（右）显示了 1 对 其他 中的一个类的示例输出。
作为多元回归的一个例子，图 7 显示了回归之间的偏差线性和非线性回归算法的输出和目标值。
更多宏可用于验证特定 MVA 方法的训练和响应。 例如，macro likelihoodrefs.C 比较似然使用的概率密度函数分类器到训练样本的归一化变量分布。还可以可视化 MLP 神经网络架构并绘制决策树（参见表 4）。
![p1](.\pictures\2.6_p1.png "figure 1")
![p2](.\pictures\2.6_p2.png "figure 2")
![p3](.\pictures\2.6_p3.png "figure 3")
![p4](.\pictures\2.6_p4.png "figure 4")
![p5](.\pictures\2.6_p5.png "figure 5")
![p6](.\pictures\2.6_p6.png "figure 6")
![p7](.\pictures\2.6_p7.png "figure 7")

## Chapter 3 Using TMVA
典型的TMVA分类和回归分析包含两个独立的状态：
 - 训练状态：多种方法被训练，测试和评估
 - 应用状态：选择的方法被应用到具体的分类和回归问题
 - TMVAClassification.C and TMVAClassificationApplication.C
 - TMVARegression.C and TMVARegressionApplication.C

![p8](.\pictures\2.6_p8.png "figure 8")
### The TMVA Factory
instantiating（实例化） a Factory object
with configuration options listed in Option-Table 1.
![t1](.\pictures\3.1_t1.png "table 1")
```cpp
TMVA::Factory* factory = new TMVA::Factory( "<JobName>", outputFile, "<options>" );
```
#### Specifying training and test data
**Code Example 6**: Registration of signal and background ROOT trees read from TFile sources. Overall signal and background weights per tree can also be specified. The TTree object may be replaced by a TChain. The trees will be later split by the factory into subsamples used for testing and training.
```cpp
// Get the signal and background trees from TFile source(s);
// multiple trees can be registered with the Factory
TTree* sigTree = (TTree*)sigSrc->Get( "<YourSignalTreeName>");
TTree* bkgTreeA = (TTree*)bkgSrc->Get( "<YourBackgrTreeName_A>") ;
TTree* bkgTreeB = (TTree*)bkgSrc->Get( "<YourBackgrTreeName_B>") ;
TTree* bkgTreeC = (TTree*)bkgSrc->Get( "<YourBackgrTreeName_C>" );
// Set the event weights per tree (these weights are applied in
// addition to individual event weights that can be specified)
Double_t sigWeight = 1.0;
Double_t bkgWeightA = 1.0, bkgWeightB = 0.5, bkgWeightC = 2.0;
// Register the trees
factory->AddSignalTree( sigTree,sigWeight);
factory->AddBackgroundTree( bkgTreeA, bkgWeightA );
factory->AddBackgroundTree( bkgTreeB, bkgWeightB );
factory->AddBackgroundTree( bkgTreeC, bkgWeightC );
```
Specifying **classification training and test data** in ROOT tree format with signal and background events being located in the same tree:
**Code Example 7**: Registration of a single ROOT tree containing the input data for signal and background,read from a TFile source. The TTree object may be replaced by a TChain. The cuts identify the event species.
```cpp
TTree* inputTree = (TTree*)source->Get( "<YourTreeName>" );
TCut signalCut = ...;
// how to identify signal events
TCut backgrCut = ...;
// how to identify background events
factory->SetInputTrees( inputTree, signalCut, backgrCut );
```
Specifying **classification data** in ROOT tree format with signal and background training/test events being located in separate trees:
**Code Example 8**: Registration of signal and background ROOT trees read from TFile sources. The first two tree are specified to be used only for training the other two only for testing. Please note that the treetype testing/training requires the inclusion of the header file TMVA/Types.h.
```cpp
#include "TMVA/Types.h"
// Get the signal and background training and test trees from TFile source(s);
TTree* sigTreeTrain = (TTree*)sigSrc->Get( "<YourSignalTrainTreeName>");
TTree* bkgTreeTrain = (TTree*)bkgSrc->Get( "<YourBackgrTrainTreeName>" );
TTree* sigTreeTest = (TTree*)sigSrc->Get( "<YourSignalTestTreeName>" );
TTree* bkgTreeTest = (TTree*)bkgSrc->Get( "<YourBackgrTestTreeName>" );
// Set the event weights (these weights are applied in
// addition to individual event weights that can be specified)
Double_t sigWeight = 1.0;
Double_t bkgWeight = 1.0;
// Register the trees
factory->AddSignalTree( sigTreeTrain, sigWeight, TMVA::Types::kTraining);
factory->AddBackgroundTree( bkgTreeTrain, bkgWeight, TMVA::Types::kTraining);
factory->AddSignalTree( sigTreeTest,sigWeight, TMVA::Types::kTesting);
factory->AddBackgroundTree( bkgTreeTest,bkgWeight, TMVA::Types::kTesting);
```
Specifying **classification training and test data** in text format:
**Code Example 9**: Registration of signal and background text files used for training and testing. Names and types of the input variables are given in the first line, followed by the values.
```cpp
// Text file format (available types: ’F’ and ’I’)
//  var1/F:var2/F:var3/F:var4/F
//  0.21293 -0.49200  -0.58425  -0.70591
//  ...
TString sigFile = "signal.txt";
// text file for signal
TString bkgFile = "background.txt"; // text file for background
Double_t sigWeight = 1.0; // overall weight for all signal events
Double_t bkgWeight = 1.0; // overall weight for all background events
factory->SetInputTrees( sigFile, bkgFile, sigWeight, bkgWeight );
```
Specifying **regression training and test data** in ROOT tree format:
**Code Example 10**: Registration of a ROOT tree containing the input and target variables. An overall weight per tree can also be specified. The TTree object may be replaced by a TChain.
```cpp
factory->AddRegressionTree( regTree, weight );
//同样也可以单独为每个event设置不同的weight
factory->SetWeightExpression( "<YourWeightExpression>" )
//或者也可以
factory->SetSignalWeightExpression("<YourSignalWeightExpression>" );
factory->SetBackgroundWeightExpression("<YourBackgroundWeightExpression>" );
```
#### Negative event weights
这东西挺麻烦，最好用：likelihood，multi-dimensional probability density estimators和decision trees.具体可见Table 7。如果对于负权重不能正确处理的方法，最好别用做训练，但可以评估表现。

boolean configuration option **IgnoreNegWeightsInTraining** Table 9 page71
#### Defining input variables, spectators and targets
**AddVariable** Method：让在输入树中用来训练MVA Method的变量在Factory中注册
加入：变量名，number type("F" and "I")（连续的浮点数还是离散的整数）
F——float&double ; I——int,short,char,unsigned
**Code Example 12**: Declaration of variables used to train the MVA methods.The := operator defines labels (third row), used for shorthand notation inscreen outputs and plots. It is also possible to define titles and units for the variables (fourth row), which are used for plotting. If labels and titles are defined, labels are used for abbreviated screen outputs, and titles for plotting.
```cpp
factory->AddVariable( "<YourDescreteVar>",'I');
factory->AddVariable( "log(<YourFloatingVar>)",'F');
factory->AddVariable( "SumLabel := <YourVar1>+<YourVar2>",'F' );
factory->AddVariable( "<YourVar3>", "Pretty Title", "Unit", 'F');
```
也可以定义“观众“变量，就是输入数据的一部分但是不用MVA训练，测试或评估。他们被复制进入TestTree。
**Code Example 13**: Various ways to declare a spectator variable, not participating in the MVA anlaysis, but written into the final TestTree.
```cpp
factory->AddSpectator( "<YourSpectatorVariable>" );
factory->AddSpectator( "log(<YourSpectatorVariable>)" );
factory->AddSpectator( "<YourSpectatorVariable>", "Pretty Title", "Unit" );
```
上面是分类部分，对于回归部分是相似的，只是不用明确数据类型
**Code Example 14**: Various ways to declare the target variables used to train a multivariate regression method. If the MVA method supports multi-target (multidimensional) regression, more than one regression target can be defined.
```cpp
factory->AddTarget( "<YourRegressionTarget1>" );
factory->AddTarget( "log(<YourRegressionTarget2>)" );
factory->AddTarget( "<YourRegressionTarget3>", "Pretty Title", "Unit" );
```
#### Preparing the training and test data
**Code Example 15**: Preparation of the internal TMVA training and test trees. The sizes (number of events)of these trees are specified in the confiration option string. For classification problems, they can be set individully for signal and background. Note that the preselection cuts are applied before the training and test samples are created, i.e., the tree sizes apply to numbers of selected events. It is also possible to choose among different methods to select the events entering the training and test trees from the source trees. All options are described in Option-Table 2. See also the text for further information
```cpp
TCut preselectionCut = "<YourSelectionString>";
factory->PrepareTrainingAndTestTree( preselectionCut, "<options>");
```
对于分类：
信号和背景事件用于训练和测试的数量需要用变量提供：
nTrain Signal, nTrain Background, nTest Signal and nTest Background
默认值0就是把（剩下的）所有都弄进去（比如train=5000,test=0你有15000就分10000给test;两个都是0就均分）

对于回归：
只要提供train和test不用区分背景、信号。

SplitMode：样例如何从树中划分（Random,Alternate,Block）SplitSeed
MixMode：出现在测试样例中的顺序，使用方式类似。

蒙特卡洛算法得出的权重不好，没关系，TMVA帮你重新算一遍。
NormMode:None（不用,谢了），NumEvents.
**Option table 2 设置参考**
![t2](.\pictures\3.1_t2.png "table 2")
#### Booking MVA methods
我们要确定方法类型，加上一个你选的特别的名字，还有一堆特殊配置。
如果一种类型用了多次，记得选不同的名字来区分。
**Code Example 16**: Example booking of the likelihood method. The first argument is a unique type enumerator (the available types can be looked up in src/Types.h), the second is a user-defined name which must be unique among all booked MVA methods, and the third is a configuration option string that is specific to the method. For options that are not explicitly set in the string default values are used, which are printed to standard output. The syntax of the options should be explicit from the above example. Individual options are separated by a ’:’. Boolean variables can be set either explicitly as MyBoolVar=True/False, or just via MyBoolVar/!MyBoolVar. All specific options are explained in the tools and MVA sections of this Users Guide. There is no difference in the booking of methods for classification or regression applications. See Appendix A on page 163 for a complete booking list of all MVA methods in TMVA.
```cpp
factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodD",
                    "!H:!V:!TransformOutput:PDFInterpol=Spline2:\
                    NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:\
                    NAvEvtPerBin=50:VarTransform=Decorrelate" );
```
#### Help option for MVA booking
the configuration option ”H”或者
```factory->PrintHelpMessage("<MethodName>")```
#### Training the MVA methods
```factory->TrainAllMethods();```
The training results are stored in the weight files which are saved in the directory weights
文件名：Jobname MethodName.weights.⟨extension⟩xml
#### Testing the MVA methods
```factory->TestAllMethods();```
The MVA outputs are stored in the test tree (TestTree)
#### Evaluating the MVA methods
```factory->EvaluateAllMethods();```
**The performance measures differ between classification and regression problems. They are summarised below.**
#### Classification performance evaluation
在训练和测试之后，分类输出的线性相关系数被打出来。
矩阵也产生。我们要评估不同分类方式的表现。
 - The **signal efficiency at three representative background efficiencies**(the efficiency is equal to 1 − rejection)obtained from a cut on the classifier output. Also given is the area of the background rejection versus signal efficiency function (the larger the area the better the performance).
 - 分离度（**separation**） of a classifier y, defined by the integral
   - $<S^2>=\frac{1}{2}\int{\frac{(\hat{y}_S(y)-\hat{y}_B(y))^2}{\hat{y}_S(y)+\hat{y}_B(y)}dy}$
   - where $\hat{y}_S$ and $\hat{y}_B$ are the signal and background PDFs of y, respectively
   - zero for identical（相同） signal and background shapes, and it is one for shapes with no overlap（重叠）.
 - The discrimination **significance** of a classifier, defined by the difference between the classifier means for signal and background divided by the quadratic sum of their root-mean-squares.区分度
这些都被写进输出的ROOT file，可以可视化。
#### Regression performance evaluation
 - The **Correlation** between two random variables X and Y is usually measured with the correlation coefficient ρ, defined by
   - $\rho{}(X,Y)=\frac{cov(X,Y)}{\sigma{}_X\sigma{}_Y}$
   - The correlation coefficient is symmetric in X and Y , lies within the interval [−1, 1], and quantifies by definition a linear relationship. 
 - The **correlation ratio** is defined by
   - $\eta{}^2(Y|X)=\frac{\sigma{}_E(Y|X)}{\sigma{}_Y}$
   - where
   - $E(Y|X)=\int{yP(y|x)dy}$
   - is the conditional expectation of Y given X with the associated conditional probability density function $P(Y|X)$.
   - $\eta{}^2$不对称，位于[0, 1]，与数据点和线性或非线性回归的拟合程度有关，哪些不构成函数关系的相关性不能被相关系数解释。
   - 下面的关系可以用来导出相关系数比$\eta{}^2$和平方相关系数$\rho{}^2$。
     - $\rho{}^2$ = $\eta{}^2$ = 1, if X and Y are in a strict linear functional relationship.
     - $\rho{}^2$ ≤ $\eta{}^2$ = 1, if X and Y are in a strict nonlinear functional relationship.
     - $\rho{}^2$ = $\eta{}^2$ < 1, if there is no strict functional relationship but the regression of X on Y is exactly linear.
     - $\rho{}^2$ < $\eta{}^2$ < 1, if there is no strict functional relationship but some nonlinear regression curve is a better fit then the best linear fit.
 - **Mutual information(互信息)信息论中出现** allows to detect any predictable relationship between two random variables, be it of functional or non-functional form. It is defined by 
   - $I(X|Y)=\sum_{X,Y}P(X,Y)In\frac{P(X,Y)}{P(X)P(Y)}$
   - where P(X, Y ) is the joint probability density function of the random variables X and Y , and P(X), P(Y ) are the corresponding marginal probabilities. 
   - 信息熵H：$H(X)=-\sum_{X}P(X)InP(X)$
   - X是离散随机数，P(X)是相关概率密度函数
I(X)和H(X)两个物理量之间的联系可以通过下面的推导得出：
![f1](.\pictures\3.1_f1.png "formula 1")
where H(X|Y ) is the conditional entropy of X given Y .
Thus mutual information is the reduction of the uncertainty in variable X due to the knowledge of Y . Mutual information is symmetric and takes positive absolute values. In the case of two completely independent variables I(X, Y ) is zero.
I(X,Y)与样例和选择的变量很相关，因此最好通过一个简单的二维随机分布图来评估就可以了。
Fig. 9有一些更形象化的展示。
![p9](.\pictures\3.1_p9.png "figure 9")
![t3](.\pictures\3.1_t3.png "table 1")

#### Overtraining
数据太少，自由度太少，用的算法太多。不同算法会有不同情况。这会导致看起来表现加强了，可以通过测试来评估过度训练的影响。也有一些特殊方法来避免。

#### Other representations of MVA outputs for classification: probabilities and probability integral transformation (Rarity)
PDFs,$\hat{y}_S(B)$.产出个体事件的分类概率或者是计算任何变化的概率积分变换。
 - 分类概率：event i
   - $P_S(i)=\frac{f_S*\hat{y}_S(i)}{f_S*\hat{y}_S(i)+(1-f_S)*\hat{y}_B(i)}$
   - where fS = NS/(NS + NB) is the expected signal fraction, and NS(B) is the expected number of signal (background) events (default is fS = 0.5)
 - 
![f10](.\pictures\3.1_p10.png "figure 10")
 - **Probability Integral Transformation**
The probability integral transformation distributions of the Likelihood and Fisher classifiers for the example used in Sec. 2 are plotted in Fig. 10. Since Fisher performs better (cf. Fig. 6 on page 12), its signal distribution is stronger peaked towards 1. By construction, the background distributions are uniform within statistical fluctuations.
### Cross Validation
略，全是细节。
### ROOT macros to plot training, testing and evaluation results
这里只讲了修改参数，略。
### The TMVA Reader
整体上与TMVA Factory的过程有异曲同工之妙。

### An alternative to the Reader: standalone C++ response classes

## 数据预处理
预处理会减少变量之间的联系，得到更好的效率。
### 传递输入变量
![f13](.\pictures\3.1_p13.png "figure 13")

## 概率密度函数，PDF类
