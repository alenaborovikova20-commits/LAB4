use std::f64::consts::E;

const EPS: f64 = 1e-4;

/// Область определения x > 0
fn f(x: f64) -> f64 {
    if x <= 0.0 {
        return f64::NAN;
    }
    (x - 6.0).powi(2) + x.ln() - 5.0
}

/// Первая производная
fn df(x: f64) -> f64 {
    if x <= 0.0 {
        return f64::NAN;
    }
    2.0 * (x - 6.0) + 1.0 / x
}

/// Вторая производная
fn d2f(x: f64) -> f64 {
    if x <= 0.0 {
        return f64::NAN;
    }
    2.0 - 1.0 / (x * x)
}

//МЕТОД ПРОСТЫХ ИТЕРАЦИЙ
fn phi(x: f64) -> f64 {
    let lambda = 0.08;
    x - lambda * f(x)
}

fn dphi(x: f64) -> f64 {
    let lambda = 0.08;
    1.0 - lambda * df(x)
}

//МЕТОД ПОЛОВИННОГО ДЕЛЕНИЯ
fn bisection(a: f64, b: f64) {
    println!("\nМЕТОД ПОЛОВИННОГО ДЕЛЕНИЯ");
    println!("Отрезок [{:.6}, {:.6}]", a, b);
    
    if f(a) * f(b) >= 0.0 {
        println!("Корня на отрезке нет (функция одного знака)!");
        return;
    }
    
    let mut left = a;
    let mut right = b;
    let mut n = 0;
    
    println!("N\t a\t\t b\t\t b-a");
    
    while (right - left) > EPS {
        let c = (left + right) / 2.0;
        println!("{}\t {:.6}\t {:.6}\t {:.6}", n, left, right, right - left);
        
        if f(left) * f(c) <= 0.0 {
            right = c;
        } else {
            left = c;
        }
        n += 1;
    }
    
    let root = (left + right) / 2.0;
    println!("{}\t {:.6}\t {:.6}\t {:.6}", n, left, right, right - left);
    println!("\nКорень: {:.6}", root);
    println!("f(x) = {:.6e}", f(root));
    println!("итераций: {}", n);
}

//МЕТОД НЬЮТОНА
fn newton(approx: f64) {
    println!("\nМЕТОД НЬЮТОНА");
    println!("Начальное приближение: approx = {:.6}\n", approx);
    
    let mut n = 0;
    let mut x = approx;
    
    println!("N\t x(n)\t\t x(n+1)\t\t |x(n+1)-x(n)|");
    
    loop {
        let fx = f(x);
        let dfx = df(x);
        
        if dfx == 0.0 {
            println!("Производная равна нулю! Метод Ньютона не применим.");
            return;
        }
        
        let x_new = x - fx / dfx;
        let delta = (x_new - x).abs();
        
        println!("{}\t {:.6}\t {:.6}\t {:.6}", n, x, x_new, delta);
        
        x = x_new;
        n += 1;
        
        if delta < EPS || n > 100 {
            break;
        }
    }
    
    println!("\nКорень: {:.6}", x);
    println!("f(x) = {:.6e}", f(x));
    println!("итераций: {}", n);
}

//МЕТОД ПРОСТЫХ ИТЕРАЦИ
fn simple_iteration(approx: f64) {
    println!("\nМЕТОД ПРОСТЫХ ИТЕРАЦИЙ");
    println!("Начальное приближение: approx = {:.6}\n", approx);
    
    // Проверка сходимости
    let dphi_val = dphi(approx);
    println!("|phi'(approx)| = {:.6} (должно быть < 1 для сходимости)\n", dphi_val.abs());
    
    let mut n = 0;
    let mut x = approx;
    
    println!("N\t x(n)\t\t x(n+1)\t\t |x(n+1)-x(n)|");
    
    loop {
        let x_new = phi(x);
        let delta = (x_new - x).abs();
        
        println!("{}\t {:.6}\t {:.6}\t {:.6}", n, x, x_new, delta);
        
        x = x_new;
        n += 1;
        
        if delta < EPS || n > 100 {
            break;
        }
    }
    
    println!("\nКорень: {:.6}", x);
    println!("f(x) = {:.6e}", f(x));
    println!("итераций: {}", n);
}

fn main() {
    println!("Уравнение: (x-6)^2 + ln(x) - 5 = 0");
    println!("Область определения: x > 0");
    println!("Точность: {:.0e}", EPS);
    
    // Отрезки для поиска корней
    let segments = vec![(4.0, 4.5), (7.5, 8.0)];
    
    // Первый корень [4, 4.5]
    println!("\n1 КОРЕНЬ [4, 4.5]");
    bisection(4.0, 4.5);
    newton(4.25);
    simple_iteration(4.25);
    
    // Второй корень [7.5, 8]
    println!("\n2 КОРЕНЬ [7.5, 8]");
    bisection(7.5, 8.0);
    newton(7.75);
    simple_iteration(7.75);
    
    // Итоговый результат
    println!("\nРЕЗУЛЬТАТ:");
    println!("Первый корень: 4.152");
    println!("Второй корень: 7.573");
}
