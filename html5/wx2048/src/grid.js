/**
 * Created by Yu on 2014/8/15.
 */
var DirectionUp = 0;
var DirectionRight = 1;
var DirectionDown = 2;
var DirectionLeft = 3;

var GridSize = 4;

var Grid = cc.Layer.extend({
    cells: null,
    size: GridSize,
    startTiles: 2,

    touchStartX: -1,
    touchStartY: -1,

    touchSize: 609,

    ctor: function () {
        this._super();
    },

    init: function () {
        if (!this._super()) {
            return false;
        }

        // read in cells
        // TODO: read state
        this.cells = this.empty();

        return true;
    },

    onEnter: function () {
        this._super();

        // add listener
        this.addListener();
    },

    addListener: function () {
        if (cc.sys.capabilities.hasOwnProperty('keyboard'))
            cc.eventManager.addListener({
                event: cc.EventListener.KEYBOARD,
                onKeyReleased: function (key, event) {
                    if (key == [cc.KEY.w] || key == [cc.KEY.up]) {
                        event.getCurrentTarget().move(DirectionUp);               //向上滑
                    }
                    else if (key == [cc.KEY.a] || key == [cc.KEY.left]) {
                        event.getCurrentTarget().move(DirectionLeft);             //向左滑
                    }
                    else if (key == [cc.KEY.d] || key == [cc.KEY.right]) {
                        event.getCurrentTarget().move(DirectionRight);            //向右滑
                    }
                    else if (key == [cc.KEY.s] || key == [cc.KEY.down]) {
                        event.getCurrentTarget().move(DirectionDown);             //向下滑
                    }
                }
            }, this);

        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: function (touch, event) {
                return event.getCurrentTarget().touchDown(touch);
            },
            onTouchMoved: function (touch, event) {

            },
            onTouchEnded: function (touch, event) {
                event.getCurrentTarget().touchUp(touch);
            }
        }, this);

        if ('touches' in cc.sys.capabilities && false) {
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesBegan: function (touches, event) {
                    event.getCurrentTarget().touchDown(touches[0]);
                },
                onTouchesMoved: function (touches, event) {
                    var target = event.getCurrentTarget();
                    var delta = touches[0].getDelta();
                    console.log("touches moved");
                },
                onTouchesEnded: function (touches, event) {
                    event.getCurrentTarget().touchUp(touches[0]);
                }
            }, this);
        }
    },

    touchDown: function (event) {
        var p = this.convertToNodeSpace(event.getLocation());
        var rect = cc.rect(0, 0, this.touchSize, this.touchSize);
        if (cc.rectContainsPoint(rect, p) && g_wx2048Layer.state == GAME_STATE_RUNNING) {
            this.touchStartX = p.x;
            this.touchStartY = p.y;
            return true;
        } else {
            this.touchStartX = -1;
            this.touchStartY = -1;
            return false;
        }
    },

    touchUp: function (event) {
        if (this.touchStartX != -1 && this.touchStartY != -1) {
            var p = this.convertToNodeSpace(event.getLocation());
            var dx = p.x - this.touchStartX;
            var absDx = Math.abs(dx);

            var dy = p.y - this.touchStartY;
            var absDy = Math.abs(dy);

            if (Math.max(absDx, absDy) > 10) {
                // (right : left) : (up : down)
                this.move(absDx > absDy ? (dx > 0 ? 1 : 3) : (dy > 0 ? 0 : 2));
            }

            // reset touchStart
            this.touchStartX = -1;
            this.touchStartY = -1;
        }
    },

    addStartTiles: function () {
        for (var i = 0; i < this.startTiles; i++) {
            this.addRandomTile();
        }
    },

    addRandomTile: function () {
        console.log("addRandomTile: ");
        if (this.cellsAvailable()) {
            var level = Math.random() < 0.9 ? 1 : 2;
            var position = this.randomAvailableCell();
            console.log("addRandomTile: " + position.x + ", " + position.y);
            var tile = new Tile(position, level);

            this.insertTile(tile);
        }
    },

    insertTile: function (tile) {
        this.cells[tile.position.x][tile.position.y] = tile;

        this.addChild(tile);
    },

    removeTile: function (tile) {
        if (tile) {
            this.removeChild(tile);

            this.cells[tile.position.x][tile.position.y] = null;
        }
    },

    cellsAvailable: function () {
        return !!this.availableCells().length;
    },

    cellAvailable: function (cell) {
        return !this.cellOccupied(cell);
    },

    cellOccupied: function (cell) {
        return !!this.cellContent(cell);
    },

    cellContent: function (cell) {
        if (this.withinBounds(cell)) {
            return this.cells[cell.x][cell.y];
        } else {
            return null;
        }
    },

    withinBounds: function (position) {
        return position.x >= 0 && position.x < this.size && position.y >= 0 && position.y < this.size;
    },

    // Find the first available random position
    randomAvailableCell: function () {
        var cells = this.availableCells();

        if (cells.length) {
            return cells[Math.floor(Math.random() * cells.length)];
        }
    },

    availableCells: function () {
        var cells = [];

        this.eachCell(function (x, y, tile) {
            if (!tile) {
                cells.push({
                    x: x,
                    y: y
                });
            }
        });

        return cells;
    },

    findFarthestPosition: function (cell, vector) {
        var previous;

        // Progress towards the vector direction until an obstacle is found
        do {
            previous = cell;
            cell = {
                x: previous.x + vector.x,
                y: previous.y + vector.y
            };
        } while (this.withinBounds(cell) &&
            this.cellAvailable(cell));

        return {
            farthest: previous,
            next: cell // Used to check if a merge is required
        };
    },

    /**
     * Call callback for every cell
     * */
    eachCell: function (callback) {
        for (var x = 0; x < this.size; x++)
            for (var y = 0; y < this.size; y++) {
                callback(x, y, this.cells[x][y]);
            }
    },

    movesAvailable: function () {
        return this.cellsAvailable() || this.tileMatchesAvailable();
    },

    tileMatchesAvailable: function () {
        var self = this;

        var tile;

        for (var x = 0; x < this.size; x++) {
            for (var y = 0; y < this.size; y++) {
                tile = this.cellContent({
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

                        var other = self.cellContent(cell);

                        if (other && other.level === tile.level) {
                            // These two tiles can be merged
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    },

    move: function (direction) {
        // return if game is not running.
        if (g_wx2048Layer.state != GAME_STATE_RUNNING)
            return;

        var self = this;
        console.log("move: direction = " + direction);

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
                tile = self.cellContent(cell);

//                if (tile) {
//                    self.insertTile(new Tile(tile.position, tile.level));
//                    self.removeTile(tile);
//                    tile.updatePosition(tile.position);
//                }

                if (tile) {
                    var positions = self.findFarthestPosition(cell, vector);
                    var next = self.cellContent(positions.next);

                    // Only one merger per row traversal?
                    if (next && next.level === tile.level && !next.mergedFrom) {
                        console.log("merge");

                        // animations
                        if (false) {
                            // move tile first
                            tile.updatePosition(positions.next);

                            // create action
                            var data = {
                                position: positions.next,
                                tile: tile,
                                next: next,
                                grid: self
                            };
                            var callback = cc.CallFunc.create(function (target, data) {
                                data.grid.removeTile(data.tile);

                                data.grid.removeChild(data.next);
                            }, this, data);
                            var delay = cc.DelayTime.create(0.2);
                            var action = cc.Sequence.create(delay, callback);
                            tile.runAction(action);
                        }

                        if (true) {
                            var merged = new Tile(positions.next, tile.level + 1, true);
                            merged.mergedFrom = [tile, next];

                            self.insertTile(merged);
                            self.removeTile(tile);

                            // TODO: remove child after next's action done.
                            self.removeChild(next);

                            // Converge the two tiles' positions
                            tile.updatePosition(positions.next);

                            // Update the score
                            g_wx2048Layer.updateScore(g_wx2048Layer.score + (Math.pow(2, merged.level) | 0));

                            // The mighty WON_VALUE tile
                            if (merged.level === WON_LEVEL)
                                g_wx2048Layer.won = true;
                        }
                    } else {
                        self.moveTile(tile, positions.farthest);
                    }

                    if (!self.positionsEqual(cell, tile)) {
                        // The tile moved from its original cell!
                        moved = true;
                    }
                }
            });
        });

        if (moved) {
            this.addRandomTile();

            //if (true) {
            if (!this.movesAvailable()) {
                // Game over!
                g_wx2048Layer.gameOver();
            }
        }
    },

    positionsEqual: function (cell, tile) {
        return cell.x === tile.position.x && cell.y === tile.position.y;
    },

    moveTile: function (tile, cell) {
        this.cells[tile.position.x][tile.position.y] = null;
        this.cells[cell.x][cell.y] = tile;

        tile.moveToPosition(cell);
    },

    prepareTiles: function () {
        this.eachCell(function (x, y, tile) {
            if (tile) {
                tile.mergedFrom = null;
                tile.savePosition();
            }
        });
    },

    // Build a list of positions to traverse in the right order
    buildTraversals: function (vector) {
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
    },

    empty: function () {
        var cells = [];

        for (var x = 0; x < this.size; x++) {
            var row = cells[x] = [];

            for (var y = 0; y < this.size; y++) {
                row.push(null);
            }
        }

        return cells;
    },

    restart: function () {
        this.eachCell(function (x, y, tile) {
            if (tile) {
                this.removeChild(tile);
            }
        }.bind(this));

        this.cells = this.empty();

        // add start tiles
        this.addStartTiles();
    },

    // Get the vector representing the chosen direction
    getVector: function (direction) {
        // Vectors representing tile movement
        var map = {
            0: { // Up
                x: 0,
                y: -1
            },
            1: { // Right
                x: 1,
                y: 0
            },
            2: { // Down
                x: 0,
                y: 1
            },
            3: { // Left
                x: -1,
                y: 0
            }
        };

        return map[direction];
    }
});

Grid.create = function () {
    var sg = new Grid();
    if (sg && sg.init()) {
        return sg;
    }
    return null;
};