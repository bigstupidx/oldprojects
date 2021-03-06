function GameManager(size, InputManager, Actuator, StorageManager, AudioManager) {
    this.size = size;
    // Size of the grid
    this.inputManager = new InputManager;
    this.storageManager = new StorageManager;
    this.actuator = new Actuator;
    this.audioManager = new AudioManager;

    // sync best score
    if (USER_TYPE != USER_TYPE_ENUM.anonymous) {
        this.storageManager.setBestScore(window.app.user.topScore);
    }

    this.startTiles = 2;

    this.inputManager.on("move", this.move.bind(this));
    this.inputManager.on("restart", this.restart.bind(this));
    this.inputManager.on("keepPlaying", this.keepPlaying.bind(this));
    this.inputManager.on("showRank", this.showRank.bind(this));
    this.inputManager.on("backToGame", this.backToGame.bind(this));
    this.inputManager.on("enter", this.enter.bind(this));
    this.inputManager.on("share", this.share.bind(this));
    this.inputManager.on("shareToGame", this.shareToGame.bind(this));

    // Do not setup if status is "prompt"
    if (window.app.status != "prompt") {
        this.setup();
    } else {
        this.setupPrompt();
    }
}

// Enter the game from prompt 
GameManager.prototype.enter = function () {
    if (window.app.status == "prompt") {
        window.app.setStatus("game");

        this.setup();

        this.audioManager.play('background-audio');
    }
}

// Restart the game
GameManager.prototype.restart = function () {
    // Clear the game won/lost message
    this.storageManager.clearGameState();

    this.actuator.uploadScore();
    this.actuator.continueGame();

    this.setup();
};

// Keep playing after winning (allows going over WON_VALUE)
GameManager.prototype.keepPlaying = function () {
    this.keepPlaying = true;
    this.actuator.continueGame();
    // Clear the game won/lost message
};

// Pause game and show rank
GameManager.prototype.showRank = function () {
    console.log("GameManager: showRank");
    window.app.showRank();
};

GameManager.prototype.backToGame = function () {
    console.log("GameManager: backToGame");
    window.app.backToGame();
    // Clear message.
    this.actuator.continueGame();
    // If game is terminated, restart it.
    if (window.app.manager.isGameTerminated()) {
        window.app.manager.restart();
    }
}

GameManager.prototype.share = function () {
    console.log("GameManager: share");
    window.app.showShare();
    //this.restart();
}

GameManager.prototype.shareToGame = function () {
    if (window.app.status == "share") {
        console.log("GameManager: shareToGame");
        window.app.shareToGame();
        // Clear message.
        this.actuator.continueGame();
        // If game is terminated, restart it.
        if (window.app.manager.isGameTerminated()) {
            window.app.manager.restart();
        }
    }
}

// Return true if the game is lost, or has won and the user hasn't kept playing
GameManager.prototype.isGameTerminated = function () {
    return this.over || (this.won && !this.keepPlaying);
};

// Set up the game for prompt
GameManager.prototype.setupPrompt = function () {
    this.grid = new Grid(this.size);
    this.score = 0;
    this.over = false;
    this.won = false;
    this.keepPlaying = false;

    // add two tiles: (4,1)(4,2)
    var value = 2;
    var position = {
        x: 0,
        y: 3
    };
    var tile = new Tile(position, value);
    this.actuator.addTile(tile);
    tile.x = 1;
    this.actuator.addTile(tile);
}

// Set up the game
GameManager.prototype.setup = function () {
    var previousState = this.storageManager.getGameState();

    // Reload the game from a previous game if present
    if (previousState) {
        this.grid = new Grid(previousState.grid.size, previousState.grid.cells);
        // Reload grid
        this.score = previousState.score;
        this.over = previousState.over;
        this.won = previousState.won;
        this.keepPlaying = previousState.keepPlaying;
    } else {
        this.grid = new Grid(this.size);
        this.score = 0;
        this.over = false;
        this.won = false;
        this.keepPlaying = false;

        // Add the initial tiles
        this.addStartTiles();
    }

    // Update the actuator
    this.actuate();
};

// Set up the initial tiles to start the game with
GameManager.prototype.addStartTiles = function () {
    for (var i = 0; i < this.startTiles; i++) {
        this.addRandomTile();
    }
};

// Adds a tile in a random position
GameManager.prototype.addRandomTile = function () {
    if (this.grid.cellsAvailable()) {
        var value = Math.random() < 0.9 ? 2 : 4;
        var tile = new Tile(this.grid.randomAvailableCell(), value);

        this.grid.insertTile(tile);
    }
};

// Sends the updated grid to the actuator
GameManager.prototype.actuate = function () {
    if (this.storageManager.getBestScore() < this.score) {
        this.storageManager.setBestScore(this.score);
    }

    // Clear the state when the game is over (game over only, not win)
    if (this.over) {
        this.storageManager.clearGameState();
    } else {
        this.storageManager.setGameState(this.serialize());
    }

    this.actuator.actuate(this.grid, {
        score: this.score,
        over: this.over,
        won: this.won,
        bestScore: this.storageManager.getBestScore(),
        terminated: this.isGameTerminated()
    });

    // update weixin desc
    if (USER_TYPE == USER_TYPE_ENUM.anonymous) {
        wxUpdateData(this.storageManager.getBestScore());
    }
};

// Represent the current game as an object
GameManager.prototype.serialize = function () {
    return {
        grid: this.grid.serialize(),
        score: this.score,
        over: this.over,
        won: this.won,
        keepPlaying: this.keepPlaying
    };
};

// Save all tile positions and remove merger info
GameManager.prototype.prepareTiles = function () {
    this.grid.eachCell(function (x, y, tile) {
        if (tile) {
            tile.mergedFrom = null;
            tile.savePosition();
        }
    });
};

// Move a tile and its representation
GameManager.prototype.moveTile = function (tile, cell) {
    this.grid.cells[tile.x][tile.y] = null;
    this.grid.cells[cell.x][cell.y] = tile;
    tile.updatePosition(cell);
};

// Move tiles on the grid in the specified direction
GameManager.prototype.move = function (direction) {
    // 0: up, 1: right, 2: down, 3: left
    var self = this;

    // Don't do anything if the game's over
    if (this.isGameTerminated())
        return;

    // Don't move when status is not game.
    if (window.app.status != 'game') {
        return;
    }

    var cell, tile;

    var vector = this.getVector(direction);
    var traversals = this.buildTraversals(vector);
    var moved = false;

    // Save the current tile positions and remove merger information
    this.prepareTiles();

    // Traverse the grid in the right direction and move tiles
    traversals.x.forEach(function (x) {
        traversals.y.forEach(function (y) {
            cell = {
                x: x,
                y: y
            };
            tile = self.grid.cellContent(cell);

            if (tile) {
                var positions = self.findFarthestPosition(cell, vector);
                var next = self.grid.cellContent(positions.next);

                // Only one merger per row traversal?
                if (next && next.value === tile.value && !next.mergedFrom) {
                    var merged = new Tile(positions.next, tile.value * 2);
                    merged.mergedFrom = [tile, next];

                    self.grid.insertTile(merged);
                    self.grid.removeTile(tile);

                    // Converge the two tiles' positions
                    tile.updatePosition(positions.next);

                    // Update the score
                    self.score += merged.value;

                    // The mighty WON_VALUE tile
                    if (merged.value === WON_VALUE)
                        self.won = true;
                } else {
                    self.moveTile(tile, positions.farthest);
                }

                if (!self.positionsEqual(cell, tile)) {
                    moved = true;
                    // The tile moved from its original cell!
                }
            }
        });
    });

    if (moved) {
        this.addRandomTile();

        // debug test
        this.over = true;

        if (!this.movesAvailable()) {
            // Game over!
            this.over = true;
        }

        this.actuate();

        // We should play a sound here.
        this.audioManager.play('move-audio');
    }
};

// Get the vector representing the chosen direction
GameManager.prototype.getVector = function (direction) {
    // Vectors representing tile movement
    var map = {
        0: {
            x: 0,
            y: -1
        }, // Up
        1: {
            x: 1,
            y: 0
        }, // Right
        2: {
            x: 0,
            y: 1
        }, // Down
        3: {
            x: -1,
            y: 0
        } // Left
    };

    return map[direction];
};

// Build a list of positions to traverse in the right order
GameManager.prototype.buildTraversals = function (vector) {
    var traversals = {
        x: [],
        y: []
    };

    for (var pos = 0; pos < this.size; pos++) {
        traversals.x.push(pos);
        traversals.y.push(pos);
    }

    // Always traverse from the farthest cell in the chosen direction
    if (vector.x === 1)
        traversals.x = traversals.x.reverse();
    if (vector.y === 1)
        traversals.y = traversals.y.reverse();

    return traversals;
};

GameManager.prototype.findFarthestPosition = function (cell, vector) {
    var previous;

    // Progress towards the vector direction until an obstacle is found
    do {
        previous = cell;
        cell = {
            x: previous.x + vector.x,
            y: previous.y + vector.y
        };
    } while (this.grid.withinBounds(cell) &&
        this.grid.cellAvailable(cell));

    return {
        farthest: previous,
        next: cell // Used to check if a merge is required
    };
};

GameManager.prototype.movesAvailable = function () {
    return this.grid.cellsAvailable() || this.tileMatchesAvailable();
};

// Check for available matches between tiles (more expensive check)
GameManager.prototype.tileMatchesAvailable = function () {
    var self = this;

    var tile;

    for (var x = 0; x < this.size; x++) {
        for (var y = 0; y < this.size; y++) {
            tile = this.grid.cellContent({
                x: x,
                y: y
            });

            if (tile) {
                for (var direction = 0; direction < 4; direction++) {
                    var vector = self.getVector(direction);
                    var cell = {
                        x: x + vector.x,
                        y: y + vector.y
                    };

                    var other = self.grid.cellContent(cell);

                    if (other && other.value === tile.value) {
                        return true;
                        // These two tiles can be merged
                    }
                }
            }
        }
    }

    return false;
};

GameManager.prototype.positionsEqual = function (first, second) {
    return first.x === second.x && first.y === second.y;
};
