use std::collections::HashMap;
use std::io;

/// Функция метода Борда
fn borda_method(n: usize, m: usize, counts: &[u32], votes: &[Vec<String>]) -> String {
    let mut scores: HashMap<String, i32> = HashMap::new();

    for i in 0..m {
        for j in 0..n {
            let score = (n - j - 1) as i32 * counts[i] as i32;
            *scores.entry(votes[i][j].clone()).or_insert(0) += score;
        }
    }

    let mut winner = String::new();
    let mut max_sum = -1;

    for (candidate, &score) in &scores {
        if score > max_sum {
            max_sum = score;
            winner = candidate.clone();
        }
    }

    print!("По Борду: {}({}) ", winner, max_sum);
    winner
}

/// Поиск позиции кандидата
fn find_position(vote: &[String], candidate: &str) -> Option<usize> {
    for (i, name) in vote.iter().enumerate() {
        if name == candidate {
            return Some(i);
        }
    }
    None
}

/// Функция метода Кондорсе
fn condorcet_method(
    n: usize,
    m: usize,
    counts: &[u32],
    votes: &[Vec<String>],
    candidates: &[String],
) -> String {
    let total_voters: u32 = counts.iter().sum();
    let mut winner = String::new();

    for i in 0..n {
        let mut is_winner = true;

        for j in 0..n {
            if i == j {
                continue;
            }

            let mut win_count = 0;

            for k in 0..m {
                let pos_i = find_position(&votes[k], &candidates[i]);
                let pos_j = find_position(&votes[k], &candidates[j]);

                if let (Some(pi), Some(pj)) = (pos_i, pos_j) {
                    if pi < pj {
                        win_count += counts[k];
                    }
                }
            }

            // Если кандидат i проигрывает j в прямом сравнении
            if win_count <= total_voters / 2 {
                is_winner = false;
                break;
            }
        }

        if is_winner {
            winner = candidates[i].clone();
            break;
        }
    }

    if !winner.is_empty() {
        println!("По Кондорсе: {}", winner);
    } else {
        println!("По Кондорсе: не определён");
    }

    winner
}

fn main() {
    println!("Введите количество кандидатов: ");
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Ошибка чтения");
    let n: usize = input.trim().parse().expect("Введите целое число");

    println!("Введите количество уникальных голосов: ");
    input.clear();
    io::stdin().read_line(&mut input).expect("Ошибка чтения");
    let m: usize = input.trim().parse().expect("Введите целое число");

    let mut candidates: Vec<String> = vec![String::new(); n];
    let mut counts: Vec<u32> = vec![0; m];
    let mut votes: Vec<Vec<String>> = vec![vec![String::new(); n]; m];

    println!("\nВведите {} строк в формате: количество кандидат1 кандидат2 ...", m);
    println!("Пример: 6 A B C\n");

    for i in 0..m {
        println!("Строка: ");
        input.clear();
        io::stdin().read_line(&mut input).expect("Ошибка чтения");
        let parts: Vec<&str> = input.trim().split_whitespace().collect();

        // Первый элемент - количество избирателей
        counts[i] = parts[0].parse().expect("Количество должно быть числом");

        // Остальные n элементов - кандидаты
        for j in 0..n {
            let name = parts[j + 1].to_string();
            votes[i][j] = name.clone();
            if i == 0 {
                candidates[j] = name;
            }
        }
    }

    println!("\nРезультаты голосования:");
    borda_method(n, m, &counts, &votes);
    condorcet_method(n, m, &counts, &votes, &candidates);
}
