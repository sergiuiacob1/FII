class A {
    double x = 0;

    A(double x) {
        this.x = x;
    }

    A(float x) {
        this.x = x;
    }
}

class B extends A {
    double y = 0;

    B(double x) {
        y = 0;
        super(x);
    }

    B() {
        super(1);
    }
}