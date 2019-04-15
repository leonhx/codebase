package com.leonhuang.common;

public class Demo {
    public static void main(String[] args) {
        Either<Integer, Option<String>> a = new Either<Integer, Option<String>>();
        Either<Integer, Option<String>> a1 = new Either<Integer, Option<String>>();
        Either<Integer, String> b = new Either<Integer, String>();
        a._1(12);
        a._2(new Some<String>("some"));
        a1._1(12);
        a1._2(new Some<String>("some"));
        b._1(12);
        b._2("some");
        System.out.println(a._1());
        System.out.println(a._2());
        System.out.println(a);
        System.out.println(a.equals(a));
        System.out.println(a.equals(a1));
        System.out.println(a.equals(b));
        System.out.println(Predef.identity().apply(a1).getClass());
    }
}
