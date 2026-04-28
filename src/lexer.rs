#[repr(C)]
#[derive(Debug, PartialEq)]
pub enum Token {
    Unknown,

    // Operators
    Plus,
    Minus,
    Star,
    Slash,
}

#[repr(C)]
pub struct Lexer<'a> {
    input: &'a str,
    remainder: &'a str,
}

impl<'a> Lexer<'a> {
    pub fn new(input: &'a str) -> Self {
        Self {
            input,
            remainder: input,
        }
    }

    fn advance(&mut self, chars: usize) {
        self.remainder = &self.remainder[chars..];
    }
}

impl<'a> Iterator for Lexer<'a> {
    type Item = Token;

    fn next(&mut self) -> Option<Self::Item> {
        use Token::*;

        // Scanning
        let start = match self
            .remainder
            .chars()
            .enumerate()
            .find(|(_, c)| !c.is_whitespace())
        {
            Some((index, _)) => index,
            _ => self.remainder.len(),
        };
        self.remainder = &self.remainder[start..];

        let mut chars = self.remainder.chars();
        let token = match chars.next()? {
            '+' => Plus,
            '-' => Minus,
            '*' => Star,
            '/' => Slash,
            _ => Unknown,
        };

        self.advance(1);

        Some(token)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn operators() {
        let mut lexer = Lexer::new("+  -   *  / ");

        assert_eq!(lexer.next(), Some(Token::Plus));
        assert_eq!(lexer.next(), Some(Token::Minus));
        assert_eq!(lexer.next(), Some(Token::Star));
        assert_eq!(lexer.next(), Some(Token::Slash));
    }

    #[test]
    fn blanks() {
        let mut lexer = Lexer::new("");
        assert_eq!(lexer.next(), None);

        let mut lexer = Lexer::new("   ");
        assert_eq!(lexer.next(), None);
    }
}
