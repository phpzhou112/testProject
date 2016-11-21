/**
 基本语法的例子
 */

//指数的用法,2e+3相当于2的小数点向后移动3位; 2e-3相当于2的小数点向左移动3位
{
    var q = 2e+3;
    var a = 2e-3;
    console.log(q);
    console.log(a);
}


/**
 js的基本类型:
 数字
 字符串
 布尔
 undefined
 null

 其他类型皆为对象
 */
var b = [1, 2, 3, 4];
function abc() {
    console.log('aaaa');
}
abc();
/**
 * isNaN()
 isFinite()
 */



function addMultiNum(a, b, c, callback) {
    var i, ar = [];
    for (i = 0; i < 3; i++) {
        ar[i] = callback(arguments[i] * 2);
    }
    return ar;
}

console.log(addMultiNum(1, 2, 3, function (a) {
    return a + 1;
}));



for(var i=1;i<4;++i);
console.log(i);  //i的值为4


/**
 * 闭包
 */

function f() {
    var ar = [];

    function printf(x) {
        return function () {
            return x;
        }
    }

    for (var i=0;i<3;i++)
    {
        ar[i] = function (x) {
            return function () {
                return x;
            }
        }(i);
    //    ar[i] = printf(i);

    }
    return ar;
}

var bbc = f();
console.log(bbc[0]());
console.log(bbc[1]());
console.log(bbc[2]());

//简单例子
function ff() {
    var i = 0;
    this.inc = function () {
        i++;
        console.log(i);
    }
}

var fff = new ff();
//fff.inc();
//fff.inc();
//fff.inc();

//简单迭代器
function setup(x) {
    var i=0;
    return function () {
        return x[i++];
    }
}
var next = setup(['a','b','c']);
//console.log(next());
//console.log(next());
//console.log(next());



/**
 * 测试call()和apply()函数对象方法
 * apply()方法第二个参数接收一个数组参数
 * call()方法第二个参数接收字符串
 */

var some_obj = {
    name:'li',
    run:function (x) {
        return 'I am '+x+"\r\n";
    }
};

var my_obj = {
    name:'zhang'
};

//console.log(some_obj.run.call(my_obj,'a','b','c'));


//立即执行函数
/*
(
    function (count) {
        if (count <5){
            arguments.callee(++count);
        }
    }
)(1);
*/
/**
 * 基本的类
 * Math,String,Date
 */

var e = new Date();
var week = e.getDay();  //获取星期
var month = e.getMonth();
var hour = e.getHours();
var minite = e.getMinutes();
var second = e.getSeconds();
var times = hour.toString()+':'+minite.toString()+':'+second.toString();
//console.log(times);

//计算2012--3012的5月12日的星期数
var stats = [0,0,0,0,0,0,0];
for (var i=2012;i<3012;i++)
{
    stats[new Date(i,5,12).getDay()]++;
}

//console.log(stats);

var re = /j*t/i;
var str = 'javascript';
//console.log(str.match(re));

/**
 * 理解原型
 * 每个函数都有一个prototype属性，初始值为空对象，prototype是属于构造器函数的属性
 * __proto__是属于某个实体对象的属性
 */

function foo() {
    this.name = 'li';
    this.color = 'red';
}

foo.prototype.price = 100;
foo.prototype.actions = function () {
    return 123;
}

var fos = new foo();

//console.log(fos.actions());

//增加string的反转函数
if(!String.prototype.reverse){
    String.prototype.reverse = function () {
        return Array.prototype.reverse.apply(this.split('')).join('');
    }
    String.prototype.constructor = String;
}

var str2 = 'abc';
//console.log(str2.reverse());



//测试原型缺陷
// function Dog()
// {
//     this.tail = true;
// }
// Dog.prototype.say = function () {
//     return 'wolf';
// }
// var d7 = new Dog();
// var d2 = new Dog();
//
// console.log(d7.say());
// console.log(d7.constructor);
// console.log(Dog.constructor.prototype);
// console.log(typeof Dog.prototype);


/*
function Animal() {
    this.age = 12;
    this.run = function () {
        console.log("haha");
    }
}

function Dog() {
    this.name = 'wang';
}

Dog.prototype = new Animal();
var dog = new Dog();
console.log(dog.name);
console.log(dog.age);
Dog.prototype.constructor = Dog;
console.log(Dog.prototype.constructor);
console.log(Dog.prototype);
console.log(Dog.constructor.prototype);
*/

//冒充继承

function Parent(fname) {
    this.fname = fname;
    this.say = function () {
        console.log(this.fname + " is running....");
    }
}

function Child(name) {
    this.Parent = Parent;
    //此行代码相当于把Parent的代码复制了过来
    this.Parent(name);
    delete this.Parent;
    this.sayH = function () {
        this.say();
    }
}

var ch = new Child('child');
var pa = new Parent('parent');
pa.say();
ch.sayH();


/**
 * 临时构造器法，封装继承方法，设定child继承自parent的扩展方法
 * 此种实现继承不能使用本身的属性，即只能继承原型增加的属性
 */
function extend(child, parent) {
    var F = function () {
    };
    F.prototype = parent.prototype;
    child.prototype = new F();
    child.prototype.constructor = child;
    //uber属性：指向父类原型
    child.uber = parent.prototype;
}
//原型属性拷贝法
function extend2(child, parent) {
    var p = parent.prototype;
    var c = child.prototype;
    for (var i in p) {
        c[i] = p[i];
    }
    c.uber = p;
}

function child() {
    this.name='child';
}
function parent() {
   // this.run = 'is run';
}
//测试一
// parent.prototype.run = 'is run';
// extend(child,parent);
// var chi = new child();
// console.log(chi.run);


//测试二,只能继承原型属性
parent.prototype.run = 'is run';
extend2(child,parent);
var chi = new child();
console.log(chi.run);

//浅拷贝
function extendCopy(p) {
    var c = {};
    for(var i in p){
        c[i] = p[i];
    }
    c.uber = p;
    return c;
}

//深拷贝
function deepCopy(p) {
    var c = c || {};
    for (var i in p){
        if(typeof p[i] === 'object'){
           c[i] = (p[i].constructor === 'Array') ? [] : {};
        }else
        {
            c[i] = p[i];
        }
    }
    return c;
}

//经典原型继承
function object(o) {
    function F(){}
    F.prototype = o;
    return new F();
}

