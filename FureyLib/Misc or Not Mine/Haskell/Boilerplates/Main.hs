-- .hs
-- Program Main Entry Point Script

import System.Environment

-- | Entry point of the program.
main :: IO ()
main = do
    args <- getArgs

    putStrLn ("Hello, Dinner!")

    -- New code here
