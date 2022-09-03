![图片](https://mmbiz.qpic.cn/mmbiz_png/QwqZcp1H2m8qWHY4IracKgL6xPJOjsswkjpcnT7X3l48Od03kSKOVzmdNEdes2ffn9YpmD51LLyDfPZDB6tgZQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

### 1 cplex python

#### 1 CPLEX的适用范围：

该引擎专门用于求解大规模的线性规划(LP)、二次规划(QP)、带约束的二次规划(QCQP)、二阶锥规划(SOCP)等四类基本问题,以及相应的混合整数规划(MIP)问题;

-   网络流问题，是 LP 的一种特殊情况，CPLEX 可以通过利用问题结构以快得多的速度对其求解。
    
-   二次规划 (QP) 问题，其中 LP 目标函数扩展为包括二次项。
    
-   二次约束规划 (QCP) 问题，在约束中包括二次项。
    
    实际上，CPLEX 可对二阶锥规划 (SOCP) 问题求解。
    
-   混合整数规划 (MIP) 问题，其中任意或所有 LP、QP 或 QCP 变量都进一步限制为采用最优解法中的整数值，并且 MIP 自身扩展为包括诸如特殊有序集合 (SOS) 和半连续变量之类的构造。
    

并且与众多优化软件及语言兼容(与C++,python, JAVA,EXCEL,Matlab等都有接口)

#### 2 安装过程(python环境)

为什么不直接pip install cplex

因为这样安装下来的是免费版本, 能够求解的变量比较少

-   安装ILOG CPLEX Optimization Studio - 中国 | IBM
    
-   在安装目录下找出cplex-> python 在文件夹中找出对应python版本的包
    
-   放到python的package下, 如果你装的是anaconda那么你的package目录是 安装目录下的 **Lib-> site-package**
    
-   import cplex 尝试一下
    

### 2 docplex

#### 1 安装

但是我们不直接用 cplex, 因为cplex 使用起来不是那么方便, 所以我们使用另一个包**docplex**它是cplex更高阶的接口,

安装过程, 在cplex安装完成之后直接 pip install docplex

官方文档在这里

#### 2 用于求解

-   cp（约束规划） 找可行解
    
-   mp（数学规划）找最优解
    

#### 3 求解步骤

-   导入包
    
-   创建模型
    
-   创建变量
    
-   添加约束
    
-   创建最优化目标
    
-   求解
    
-   保存( 可选 )
    

#### 4 .1 导入包

```
from docplex.mp.model import Model # 创建模型Model(name = None)
```

#### 4.2 变量类型

```
#-------------变量类型如下--------#-----[lb, ub]#------------------------连续变量------------------------continuous_var(lb=None, ub=None, name=None)continuous_var_list(keys, lb=None, ub=None, name=<class 'str'>, key_format=None)#------------------------整型------------------------integer_var(lb = None, ub = None, name = None)# lb – The lower bound of the variable, or None. The default is 0.# ub – The upper bound of the variable, or None, to use the default. The default is model infinity.# name – An optional name for the variable.integer_var_list(keys, lb=None, ub=None, name=<class 'str'>, key_format=None)# keys – 对象序列、迭代器或正整数。如果传递一个整数，则将其解释为要创建的变量数。# lb – 变量的下限。接受浮点数、数字列表或函数。如果所有变量共享相同的下限，请使用数字。否则，要么使用显式数字列表，要么使用函数（如果下限因键而异），在这种情况下，将在键中的每个键上调用该函数。“无”表示使用默认下限 （0）。# ub – 变量的上限。接受浮点数、数字列表、函数或 None。如果所有变量共享相同的上限，请使用数字。否则，要么使用显式数字列表，要么使用函数（如果上限因键而异），在这种情况下，将在键中的每个键上调用该函数。“无”表示使用默认上限（模型无穷大）。#------------------------01变量------------------------model.binary_var(name =  None)binary_var_list(keys, lb=None, ub=None, name=<class 'str'>, key_format=None)
```

#### 4.3 添加约束

```
#向模型添加线性约束add_constraint(ct， ctname = None)# ct 是约束表达式, 操作符有,  <=（小于或等于）、== （等于） 和 >=（大于或等于）add_constraint(cts， name = None)# m.add_constraints（[x >= 1， y<= 3]， [“c1”， “c2”]）# 两个都为列表# 返回新添加的约束的列表。
```

#### 4.4 添加时间限制

```
m.time_limit()
```

#### 4.5 求解问题

```
solve = m.solve()#获取所有的变量解print(solve._get_all_values()) #获取解的详细信息，如时间，gap值等print(solve.solve_details)
```

#### 5.1  实例1

![图片](https://mmbiz.qpic.cn/mmbiz_png/QwqZcp1H2m9uyTQRXFIrXSGbujWfz8ZsibqwaaCiconolLR3ibddp14ndZrBa9Ueic9HYFGiczl5KErY1Y4DajAUOSA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

```
from docplex.mp.model import Model  #导出库，只用这一个就够了model = Model('LP') #可命名model为 'LP'#创建列表var_list = [i for i in range(0, 4)] #创建变量列表X = model.continuous_var_list(var_list, lb=0, name='X') model.maximize(3 * X[0] + 5 * X[1] + 4 * X[2])  #设定目标函数#添加约束条件model.add_constraint(2 * X[0] + 3 * X[1] <= 1500)model.add_constraint(2 * X[1] + 4 * X[2] <= 800)model.add_constraint(3 * X[0] + 2 * X[1] + 5 * X[2] <= 2000)sol = model.solve() #求解模型print(sol)  #打印结果
```

```
from docplex.mp.model import Modelm = Model()x = {i: m.integer_var(lb = 0,) for i in range(2)}print(x)m.maximize(800* x[0] + 300 * x[1])m.add_constraint(6* x[0] +8 *x[1]<= 120)m.add_constraint(10 * x[0] + 5 * x[1]<= 100)solve = m.solve()print(solve)#设置时间m.time_limit()#获取所有的变量解print(solve._get_all_values()) #获取解的详细信息，如时间，gap值等print(solve.solve_details)
```

#### 5.2 求解旅行商问题

```
#---------------求解TSP问题------------------------from docplex.mp.model import Modelnum_city = 10model = Model("TSP")#用字典存储变量x = {(i,j): model.binary_var(name = 'x_{0}_{1}'.format(i, j))  for i in range(num_city) for j in range(num_city)}#约束for i in range(num_city):    temp1 = model.sum(x[i,j] for j in range(num_city) if i != j)    model.add_constraint(temp1 ==1 ,ctname = 'cons_start_{0}'.format(i))for j in range(num_city):    temp =model.sum(x[i,j] for i in range(num_city) if i != j)    model.add_constraint(temp ==1, ctname = 'cons_end{}'.format(j))temp = model.sum(x[i,j] for i in range(num_city) for j in range(num_city) if j != j)model.minimize(temp)model.export('TSP.lp')solve = model.solve(log_output = True)#结果展示，将非零变量的结果导入pandas列表并导入到csv文件if solve:    var_dict = solve.get_value_df(x)    output_dict = var_dict[var_dict['value'] > 0]    output_dict.to_csv('output.csv')
```

#### 5.3 添加二次约束

```
from docplex.mp.model import Model  mdl = Model(name='qpex1')#decision variablesx = {b: mdl.continuous_var(0,40,name="x"+str(b)) for b in range(0,3)}# Constraintmdl.add_constraint( - x[0] +     x[1] + x[2] <= 20, 'ct1')mdl.add_constraint(x[0] - 3 * x[1] + x[2] <= 30,'ct2')mdl.add_constraint(x[0] * x[0] <= 30,'quad')# Objectivemdl.maximize(x[0] + 2 * x[1] + 3 * x[2]-\             0.5 * ( 33*x[0]*x[0] + 22*x[1]*x[1] + 11*x[2]*x[2] -\                     12*x[0]*x[1] - 23*x[1]*x[2] ))msol=mdl.solve()# Dislay solutionfor v in mdl.iter_continuous_vars():   print(v," = ",v.solution_value)print("objective : ",msol.get_objective_value() )
```