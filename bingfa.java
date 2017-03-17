/**
 * executor把工作任务提交和执行分离开来
 */

import cn.cast.myEnum;

import java.util.Random;
import java.util.concurrent.*;
import java.util.concurrent.FutureTask;
import java.util.concurrent.Future;

//executorservice提供了终止的方法,shutdown()和shutdownnow()
import java.util.concurrent.ExecutorService;
/**
 * 主程序
 */
public class main {
    public static void main(String[] argv){

        //创建固定线程池,适用于负载较重的服务器
        Executor executor = Executors.newFixedThreadPool(5);
        //此类型线程池可以延长或定时任务
        ExecutorService service = Executors.newScheduledThreadPool(5);

        //runnable的返回结果拿不到
        Runnable r = new Runnable() {
            @Override
            public void run() {
                System.out.print("good" + Thread.currentThread().getId());
            }
        };

        executor.execute(r);
    }
}

/**
 * Callable接口类似于Runnable，从名字就可以看出来了，
 * 但是Runnable不会返回结果，并且无法抛出返回结果的异常，
 * 而Callable功能更强大一些，被线程执行后，可以返回值，
 * 这个返回值可以被Future拿到，也就是说，Future可以拿到异步执行任务的返回值
 *
 */
class Func
{
    public void test(){
        Callable<Integer> callable = new Callable<Integer>() {
            public Integer call() throws Exception {
                return new Random().nextInt(100);
            }
        };
        FutureTask<Integer> future = new FutureTask<>(callable);
        Executor executor = Executors.newFixedThreadPool(5);
       // new Thread(future).start();
        executor.execute(future);
        try {
            Thread.sleep(5000);// 可能做一些事情
            System.out.println(future.get());
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }
    }
}