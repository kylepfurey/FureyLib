-- .hs
-- Name
-- Creator

module Struct where


-- DATA

-- | Template structure script.
data Struct = Struct {
    -- | Example x variable.
    x :: Float,

    -- | Example y variable.
    y :: Float
} deriving (Show, Eq)


-- CONSTRUCTORS

-- | Initializes a new structure.
newStruct :: Float -> Float -> Struct
newStruct x y = Struct { x = x, y = y }

-- | Initializes a zeroed structure.
zeroStruct :: Struct
zeroStruct = Struct { x = 0, y = 0 }


-- FUNCTIONS

-- | Returns the magnitude of the given structure.
structMagnitude :: Struct -> Float
structMagnitude struct
    | x struct == 0 && y struct == 0 = 0
    | otherwise = sqrt (x struct * x struct + y struct * y struct)

-- | Normalizes the given structure.
structNormalize :: Struct -> Struct
structNormalize struct
    | magnitude == 0 = struct
    | otherwise = newStruct (x struct / magnitude) (y struct / magnitude)
    where magnitude = structMagnitude (struct)
