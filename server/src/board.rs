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

impl Default for Cell {
    fn default() -> Self {
        Self::Empty(0)
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
}
