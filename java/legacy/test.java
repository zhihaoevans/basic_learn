/*
 * 主题说明：构造器最小示例——new 对象时自动执行同名构造方法（历史遗留示例，原位于 java/ 根目录）。
 * 运行命令：java java/legacy/test.java
 * 预期输出（关键行）：小狗的名字是 : tommy
 */
public class Puppy{
    public Puppy(String name){
        //这个构造器仅有一个参数：name
        System.out.println("小狗的名字是 : " + name );
    }
    public static void main(String[] args){
        // 下面的语句将创建一个Puppy对象
        Puppy myPuppy = new Puppy( "tommy" );
    }
}