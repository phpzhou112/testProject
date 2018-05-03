<?php

/**
 * Created by PhpStorm.
 * User: zhou
 * Date: 2018/3/23
 * Time: 11:17
 */
class Node
{
    public $next;
    public $value;

    public function __construct()
    {
        $this->value = null;
        $this->next = null;
    }
}

class ListLink
{
    public function insert($head, $value)
    {
        $node = new Node();
        $node->value = $value;
        $node->next = $head->next;
        $head->next = $node;
    }

    public function traverse($head)
    {
        while ($head->next) {
            echo $head->next->value . "\r\n";
            $head = $head->next;
        }
    }
}

$node = new Node();
$link = new ListLink();
for ($i = 0; $i < 5; ++$i) {
    $link->insert($node, $i);
}


//$link->traverse($node);

//$queue = new SplQueue();
//
//$queue->push(1);
//$queue->push(2);
//$queue->push(3);
//while (!$queue->isEmpty()){
//   // $queue->unshift(1);
//    echo $queue->shift();
//}

//必须加上该参数，定时器才会起作用
/*
declare(ticks = 1);
function sig()
{
    echo 'good';
    pcntl_alarm(1);
}

while(true){
    pcntl_alarm(1);
    pcntl_signal(SIGALRM, "sig");
    sleep(5);
}
*/

/*包括几个方法:

1.守护进程
2.socket连接
*/


class Graph
{
    private $vexNum;  //顶点数
    private $arcNum;  //边数
    private $adjest = [];   //二维数组
    private $visited = [];   //访问的数组

    public function __construct($vexNum = '', $arcNum = '')
    {
        $this->vexNum = $vexNum;
        $this->arcNum = $arcNum;
    }

    public function createGraph($vexNum, $arcNum)
    {
        $vexNum = intval($vexNum);
        $arcNum = intval($arcNum);
        $graph = new Graph($vexNum, $arcNum);
        for ($i = 0; $i < $vexNum; ++$i) {
            for ($j = 0; $j < $arcNum; ++$j) {
                $graph->adjest[$i][$j] = 0;
            }
        }
        return $graph;
    }

    /**
     * @param $graph
     * @param $v
     */
    public function Dfs($graph, $v)
    {
        $this->visited[$v] = true;
        echo $v . ' ';
        for ($j = 0; $j < $graph->vexNum; ++$j) {
            if ($graph->adjest[$v][$j] == 1 && $this->visited[$j] == false) {
                $this->Dfs($graph, $j);
            }
        }
    }

    public function DfsTraverse($graph)
    {
        for ($v = 0; $v < $graph->vexNum; ++$v) {
            $this->visited[$v] = false;
        }
        for ($j = 0; $j < $graph->vexNum; ++$j) {
            if ($this->visited[$j] == false) {
                $this->Dfs($graph, $j);
            }
        }
    }


    public function Bfs($graph)
    {
        $queue = new SplQueue();
        for ($v = 0; $v < $graph->vexNum; ++$v) {
            $this->visited[$v] = false;
        }

        for ($v = 0; $v < $graph->vexNum; ++$v) {
            if ($this->visited[$v] == false) {
                $queue->push($v);
                $this->visited[$v] = true;
                while (!$queue->isEmpty()) {
                    $t = $queue->shift();
                    echo $t + 1 . ' ';
                    for ($j = 0; $j < $graph->vexNum; ++$j) {
                        if ($graph->adjest[$v][$j] == 1 && $this->visited[$j] == false) {
                            $queue->push($j);
                            $this->visited[$j] = true;
                        }
                    }
                }
            }
        }
    }

    public function stack()
    {
        $stack = new SplStack();
        $stack->push(1);
        $stack->push(2);
        $stack->push(3);
        echo $stack->pop();
        echo $stack->pop();
        echo $stack->pop();
    }
}

$graph = new Graph();
//$g = $graph->createGraph(3, 4);
//$graph->DfsTraverse($g);
//$graph->Bfs($g);
//$graph->stack();
$arr = [];
$graph = serialize($graph);
$arr[$graph] = 1;
var_dump($arr);

