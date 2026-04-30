use std::{iter::Peekable, str::CharIndices};

#[repr(C)]
#[derive(Debug, PartialEq)]
pub enum Token {
    Unknown,

    // Literals
    Integer(i64),

    // Operators
    Plus,
    Minus,
    Star,
    Slash,
}

#[repr(C)]
pub struct Lexer<'a> {
    input: &'a str,
    iter: Peekable<CharIndices<'a>>,
}

impl<'a> Lexer<'a> {
    pub fn new(input: &'a str) -> Self {
        Self {
            input,
            iter: input.char_indices().peekable(),
        }
    }

    pub fn lex(&mut self) -> Option<Token> {
        use Token::*;

        // Scanning - skip whitespaces
        let (i, c) = self.iter.find(|(_, c)| !c.is_whitespace())?;

        // Lexing
        let token = match c {
            '0'..='9' => {
                let start = i;
                let end = match self.peek_while(|&(_, c)| c.is_digit(10)) {
                    Some((end, _)) => end,
                    None => self.input.len(),
                };
                // TODO Handle overflow error
                Integer(
                    self.input[start..end]
                        .parse::<i64>()
                        .expect("This subslice should be comprised of ASCII digits"),
                )
            }
            '+' => Plus,
            '-' => Minus,
            '*' => Star,
            '/' => Slash,
            _ => Unknown,
        };

        Some(token)
    }

    fn peek_while<P>(&mut self, mut predicate: P) -> Option<(usize, char)>
    where
        P: FnMut(&(usize, char)) -> bool,
    {
        while predicate(self.iter.peek()?) {
            self.iter.next();
        }
        self.iter.peek().copied()
    }
}

impl<'a> Iterator for Lexer<'a> {
    type Item = Token;

    fn next(&mut self) -> Option<Self::Item> {
        self.lex()
    }
}

#[cfg(test)]
mod tests {
    use super::Token::*;
    use super::*;

    #[test]
    fn literals() {
        let mut lexer = Lexer::new(" 12  3 4 ");
        assert_eq!(lexer.next(), Some(Integer(12)));
        assert_eq!(lexer.next(), Some(Integer(3)));
        assert_eq!(lexer.next(), Some(Integer(4)));
    }

    #[test]
    fn operators() {
        let mut lexer = Lexer::new("+  -   *  / ");

        assert_eq!(lexer.next(), Some(Plus));
        assert_eq!(lexer.next(), Some(Minus));
        assert_eq!(lexer.next(), Some(Star));
        assert_eq!(lexer.next(), Some(Slash));
    }

    #[test]
    fn blanks() {
        let mut lexer = Lexer::new("");
        assert_eq!(lexer.next(), None);

        let mut lexer = Lexer::new("   ");
        assert_eq!(lexer.next(), None);
    }
}
