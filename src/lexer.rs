use std::{iter::Peekable, str::CharIndices};

#[repr(C)]
#[derive(Debug, PartialEq)]
pub enum Token<'a> {
    Unknown,

    Variable(&'a str),

    // Literals
    Integer(i64),

    // Operators
    Equals,
    Plus,
    Minus,
    Star,
    Slash,

    // Punctuation
    Semicolon,
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

    pub fn lex(&mut self) -> Option<Token<'a>> {
        use Token::*;

        // Scanning - skip whitespaces
        let (i, c) = self.iter.find(|(_, c)| !c.is_whitespace())?;

        // Lexing
        let token = match c {
            '@' => {
                if let Some((start, c)) = self.iter.next()
                    && c.is_alphanumeric()
                {
                    let end = match self.peek_while(|&(_, c)| c.is_alphanumeric()) {
                        Some((end, _)) => end,
                        None => self.input.len(),
                    };
                    Variable(&self.input[start..end])
                } else {
                    Unknown
                }
            }
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
            '=' => Equals,
            '+' => Plus,
            '-' => Minus,
            '*' => Star,
            '/' => Slash,
            ';' => Semicolon,
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
    type Item = Token<'a>;

    fn next(&mut self) -> Option<Self::Item> {
        self.lex()
    }
}

#[cfg(test)]
mod tests {
    use super::Token::*;
    use super::*;

    #[test]
    fn mixed() {
        let tokens: Vec<Token> = Lexer::new(
            "
                @val = 7 * 42;
            ",
        )
        .collect();

        assert_eq!(
            tokens,
            vec![
                Variable("val"),
                Equals,
                Integer(7),
                Star,
                Integer(42),
                Semicolon,
            ],
        );
    }

    #[test]
    fn literals() {
        let tokens: Vec<Token> = Lexer::new(" 12  3 4 ").collect();

        assert_eq!(tokens, vec![Integer(12), Integer(3), Integer(4)]);
    }

    #[test]
    fn operators() {
        let tokens: Vec<Token> = Lexer::new("+  -   *  / ").collect();

        assert_eq!(tokens, vec![Plus, Minus, Star, Slash,],);
    }

    #[test]
    fn blanks() {
        let mut lexer = Lexer::new("");
        assert_eq!(lexer.next(), None);

        let mut lexer = Lexer::new("   ");
        assert_eq!(lexer.next(), None);
    }
}
