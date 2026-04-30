use std::str::CharIndices;

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
    iter: CharIndices<'a>,
}

impl<'a> Lexer<'a> {
    pub fn new(input: &'a str) -> Self {
        Self {
            input,
            iter: input.char_indices(),
        }
    }

    pub fn lex(&mut self) -> Option<Token> {
        use Token::*;

        // Scanning - skip whitespaces
        let (i, c) = self.iter.find(|(_, c)| !c.is_whitespace())?;

        // Lexing
        let token = match c {
            '0'..='9' => {
                let mut peeker = self.iter.clone();
                let start = i;
                let end = match peeker.find(|(_, c)| !c.is_digit(10)) {
                    Some((end, _)) => end,
                    None => self.input.len(),
                };
                if end - start > 1 {
                    let _ = self.iter.nth(end - start - 1 - 1);
                }
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
