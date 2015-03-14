/**
 * Created by Yu on 2014/9/2.
 */
RankScene = cc.Scene.extend({
    focus: 2, // default is 店内

    ctor: function () {
        this._super();

        // bg
        this.bg = new Decorate(true, true, true, false);
        this.addChild(this.bg);

        this.rankBg = cc.Sprite.create(res.rank_bg_png);
        this.rankBg.setPosition(0, 0);
        this.rankBg.setAnchorPoint(0, 0);
        this.addChild(this.rankBg);

        // back button
        var sprite = cc.Sprite.create(res.rank_back_button_png);
        var button = cc.MenuItemSprite.create(sprite, null, this.back, this);
        button.setPosition(320, 1136 - 965);

        // score tab
        var scoreTabSprite = cc.Sprite.create(res.rank_score_tab_png);
        scoreTabSprite.setPosition(164, 1136 - 292);
        this.addChild(scoreTabSprite);

        // tab buttons
        var tabSprites = [
            res.uz_tab_png,                 // 经销商区域
            res.uz_tab_selected_png,
            res.un_tab_png,                 // 经销商全国
            res.un_tab_selected_png,
            res.ug_tab_png,                 // 店内
            res.ug_tab_selected_png,
            res.gz_tab_png,                 // 个人区域
            res.gz_tab_selected_png,
            res.gn_tab_png,                  // 个人全国
            res.gn_tab_selected_png
        ];
        var tabPositions = [
            {x: 315, y: 1136 - 292},
            {x: 466, y: 1136 - 292},
            {x: 164, y: 1136 - 349},
            {x: 315, y: 1136 - 349},
            {x: 466, y: 1136 - 349}
        ];
        this.tabSprites = [];
        this.tabSelectedSprites = [];
        this.tabButtons = [];
        for (var i = 0; i < 5; i++) {
            this.tabSprites[i] = cc.Sprite.create(tabSprites[i * 2]);
            this.tabSelectedSprites[i] = cc.Sprite.create(tabSprites[i * 2 + 1]);
            this.tabButtons[i] = new cc.MenuItemSprite(this.tabSprites[i], null, this.select, this);
            this.tabButtons[i].setPosition(tabPositions[i].x, tabPositions[i].y);
        }

        // menu
        this.menu = cc.Menu.create(button);
        this.menu.setAnchorPoint(0, 0);
        this.menu.setPosition(0, 0);
        this.addChild(this.menu);

        // add menu item sprites
        for (var i = 0; i < 5; i++) {
            this.menu.addChild(this.tabButtons[i]);
        }

        // add dummy grid
        var grid = cc.Sprite.create(res.rank_grid_png);
        grid.setPosition(320, 1136 / 2);
        this.addChild(grid);

        // add table
        this.tableView = new cc.TableView(this.dataSource, cc.size(440, 6 * 83));
        this.tableView.setDirection(cc.SCROLLVIEW_DIRECTION_VERTICAL);
        this.tableView.x = 320 - (440 / 2);
        this.tableView.y = 1136 - (608 + 3 * 83);
        this.tableView.setDelegate(this);
        this.tableView.setVerticalFillOrder(cc.TABLEVIEW_FILL_TOPDOWN);
        this.addChild(this.tableView);

        // set focus
        this.setFocus(this.focus);
    },

    back: function () {
        console.log("rank scene: back");
        cc.director.popScene();
    },

    select: function (target) {
        for (var i = 0; i < 5; i++) {
            if (target == this.tabButtons[i])
                break;
        }
        this.setFocus(i);
    },

    setFocus: function (index) {
        // unselect old focus
        this.tabButtons[this.focus].setNormalImage(this.tabSprites[this.focus]);
        this.focus = index;
        // select new focus
        this.tabButtons[this.focus].setNormalImage(this.tabSelectedSprites[this.focus]);
        // set data source
        var source = null;
        switch (this.focus) {
            case 0:
                source = user.rank.gzAll;
                break;
            case 1:
                source = user.rank.gnAll;
                break;
            case 2:
                source = user.rank.ugAll;
                break;
            case 3:
                source = user.rank.uzAll;
                break;
            case 4:
                source = user.rank.unAll;
                break;
            default:
                break;
        }
        this.dataSource.setSource(source);
        this.tableView.reloadData();
    },

    dataSource: {
        source: null,

        setSource: function (source) {
            this.source = source;
        },

        getString: function (idx, col) {
            var string = "";
            var item = this.source[idx];
            if (col == 0) {
                var idxString = (++idx);
                string = "第" + idxString + "名";
            } else if (col == 1) {
                string = item["zone"];
            } else if (col == 2) {
                string = item["dealer"];
            } else if (col == 3) {
                string = item["name"];
                if (string == null) {
                    string = "";
                }
            } else if (col == 4) {
                string = parseInt(Number(item["score"])) + "分";
            }
            return string;
        },

        numberOfCellsInTableView: function () {
            if (this.source == null) {
                return 0;
            } else {
                return this.source.length;
            }
        },

        tableCellSizeForIndex: function (table, idx) {
            return cc.size(table.width, 83);
        },

        layout: [
            68,
                223 - 68,
                291 - 223,
                342 - 291,
                440 - 342
        ],

        tableCellAtIndex: function (table, idx) {
            idx = idx.toFixed(0);
            var cell = table.dequeueCell();
            if (!cell) {
                cell = new cc.TableViewCell();
                for (var i = 0; i < 5; i++) {
                    var label = new cc.LabelTTF("", "Arial", 20.0,
                        cc.size(this.layout[i], 83), cc.TEXT_ALIGNMENT_CENTER, cc.VERTICAL_TEXT_ALIGNMENT_CENTER);
                    var x = 0;
                    for (var j = 0; j < i; j++) {
                        x += this.layout[j];
                    }
                    label.setPosition(x + this.layout[i] / 2, 83 / 2);
                    label.tag = i;
                    label.setColor(cc.color(170, 90, 27, 255));
                    cell.addChild(label);
                    label.setString(this.getString(idx, i));
                }

                var sprite = cc.Sprite.create(res.rank_line_png);
                sprite.setPosition(440 / 2, 83 - 3 / 2);
                sprite.tag = 10;
                cell.addChild(sprite);
                if (idx == 0) {
                    sprite.setVisible(false);
                } else {
                    sprite.setVisible(true);
                }
            } else {
                for (var i = 0; i < 5; i++) {
                    var label = cell.getChildByTag(i);
                    label.setString(this.getString(idx, i));
                }

                var sprite = cell.getChildByTag(10);
                if (idx == 0) {
                    sprite.setVisible(false);
                } else {
                    sprite.setVisible(true);
                }
            }

            return cell;
        }
    }
});