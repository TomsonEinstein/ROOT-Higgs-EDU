# TMVA User Guide Notes
Contributors:周飞扬，陈瑞琪

## Chapter 1 Introductions
 - TMVA use “supervised learnning” algorithms 监督学习
 - Course 过程
   - classification（分类）:discribes a decision boundary
   - regression（回归）:define the target value
 - 这个包的主要内容
   - Rectangular cut optimisation (binary splits, Sec. 8.1).  矩形切割优化
   - Projective likelihood estimation (Sec. 8.2). 射影似然估计
   - Multi-dimensional likelihood estimation (PDE range-search – Sec. 8.3, PDE-Foam – Sec. 8.4, and k-NN – Sec. 8.5).  多维似然估计
   - Linear and nonlinear discriminant analysis (H-Matrix – Sec. 8.6, Fisher – Sec. 8.7, LD – Sec. 8.8, FDA – Sec. 8.9).  线性和非线性判别分析
   - Artificial neural networks (three different multilayer perceptron implementations – Sec. 8.10).  人工神经网络
   - Support vector machine (Sec. 8.12).  支持向量机
   - Boosted/bagged decision trees (Sec. 8.13). 增加/袋装决策树
   - Predictive learning via rule ensembles (RuleFit, Sec. 8.14).  通过规则集成的预测学习
   - A generic boost classifier allowing one to boost any of the above classifiers (Sec. 10). 一个通用的增强分类器，允许增强上面任何一个分类器
   - A generic category classifier allowing one to split the training data into disjoint categories with independent MVAs.一个通用类别分类器，允许一个人分割训练数据为不相交的类别与
独立的mva。
 - 