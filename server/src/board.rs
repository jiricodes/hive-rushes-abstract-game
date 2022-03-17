use std::fmt;

/// Enum to handle state of a board cell
///
/// Empty and Player options hold their current level (0-3).
/// Dome is the end state of a cell and cannot be accessed.
#[derive(Debug, Clone, Copy)]
pub enum Cell {
    Empty(u8),
    Player(u8),
    Dome,
}

impl Cell {
    fn as_string(&self) -> String {
        match *self {
            Self::Empty(val) => format!("E{}", val),
            Self::Player(val) => format!("P{}", val),
            Self::Dome => String::from("D4"),
        }
    }
}

impl Default for Cell {
    fn default() -> Self {
        Self::Empty(0)
    }
}

impl fmt::Display for Cell {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.as_string())
    }
}

#[derive(Debug)]
pub struct Board {
    board: [[Cell; 5]; 5],
}

impl Board {
    pub fn new() -> Self {
        Self {
            board: [[Cell::default(); 5]; 5],
        }
    }

    pub fn set_cell(&mut self, row: usize, col: usize, cell: Cell) -> Result<(), &'static str> {
        if row >= 5 || col >= 5 {
            return Err("Cell out of bounds");
        }
        self.board[row][col] = cell;
        Ok(())
    }
}

impl fmt::Display for Board {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let mut out = String::new();
        for line in self.board.iter() {
            for c in line.iter() {
                out += &format!("{} ", c);
            }
            out.pop();
            out += "\n";
        }
        out.pop();
        write!(f, "{}", out)
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn basic() {
        let mut b = Board::new();
        let ret = b.set_cell(2, 2, Cell::Player(1));
        assert!(ret.is_ok());
        let ret = b.set_cell(5, 2, Cell::Player(1));
        assert!(ret.is_err());
        let ret = b.set_cell(2, 3, Cell::Dome);
        assert!(ret.is_ok());
        println!("{}", b);
    }
}
