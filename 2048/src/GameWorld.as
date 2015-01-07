package
{
	import flash.display.Screen;
	import flash.display.Sprite;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.media.Sound;
	import flash.net.URLRequest;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.ui.GameInput;
	import flash.ui.Keyboard;
	import flash.ui.Mouse;

	public class GameWorld extends Sprite {
		public static const square_length 		:int = 100;
		public static const square_distance  	:int = 20;
		private var m_map						:Map;
		
		private var title						:Title;
		
		public var boxes						:Array = [16];
		public var mp3_hit							:Sound;
		private var mp3_move						:Sound;
		private var layout_x 					:Array = new Array(20, 140, 260, 380, 20, 140, 260, 
																380, 20, 140, 260, 380, 20, 140, 260, 380); 

		private var layout_y 					:Array = new Array(20, 20, 20, 20, 140, 140, 140, 140,
																260, 260, 260, 260, 380, 380, 380, 380); 
		
		private var LEFT						:Array = new Array(0, 1, 2, 3, 4, 5, 6, 7, 8,
																9, 10, 11, 12, 13, 14, 15);
		private var DOWN 						:Array = new Array(12, 8, 4, 0, 13, 9, 5, 1, 
																14, 10, 6, 2, 15, 11, 7, 3);
		private var UP							:Array = new Array(0, 4, 8, 12, 1, 5, 9, 13,
																2, 6, 10, 14, 3, 7, 11, 15);
		private var RIGHT						:Array = new Array(3, 2, 1, 0, 7, 6, 5, 4, 11,
																10, 9, 8, 15, 14, 13, 12);
		private var modified					:Array = [16];
		
		private var map_x						:int = 50;
		private var map_y 						:int = 150;
		
		private var score						:int;
		private var best						:int;
		public var change						:Boolean;
		private var end 						:End;
		
		public var move							:Move;
		public var addbox 						:AddBox;
			
		public function GameWorld() {
			addbox = new AddBox(this);
			move = new Move(this);
			
			m_map = new Map();
			this.addChild(m_map);
			m_map.x = map_x;
			m_map.y = map_y;
		
			title = new Title(map_x);
			title.newGame.addEventListener(MouseEvent.CLICK, Restart);
			this.addChild(title);
			
			this.start();

			mp3_hit = new Sound(new URLRequest("hit.mp3"));
			mp3_move = new Sound(new URLRequest("move.mp3"));
			this.addEventListener(KeyboardEvent.KEY_DOWN, keyDown);		
			
			best = 0;
			score = 0;
		}
		
		private function Restart(e:MouseEvent):void {
			if(null != end) {
				this.removeChild(end);
				end = null;
			}
			stage.focus = stage;
			trace(e);
			for(var i:int = 0; i < 16; i++)
				del(i);
			this.start();
		}
		
		private function updateDown(oldPos:int, newPos:int, newVal:int):void {
			if(-1 == newPos)
				return ;
			move.addMoveObject(layout_x[oldPos] + map_x, layout_y[oldPos] + map_y, 
									layout_x[newPos] + map_x, layout_y[newPos] + map_y, newPos);
			del(oldPos);
			del(newPos);
			add(newPos, newVal);
		}
		
		private function putDown(index:Array, pos:int) {
			var posRight:int = -1;
			var val:int = boxes[index[pos]].getVal();
			for(var i:int = pos - 1;  ;i --) {
				if(null == boxes[index[i]])	
					posRight = index[i];
				else if(false == modified[index[i]]) {
					if(boxes[index[i]].getVal() == val) {
						updateDown(index[pos], index[i], val + 1);
						modified[index[i]] = true;
					
						var result:int = 1;
						for(var f:int = 0; f < val + 1; f++)
							result *= 2;
						score += result;
						title.score.updateName(score.toString());
						if(score > best) {
							best = score;
							title.best.updateName(score.toString());
						}
						return ;
					}
					updateDown(index[pos], posRight, val);
					return ;				
				}
				
				if(0 == (i % 4))
					break;
			}
			updateDown(index[pos], posRight, val);
		}
		
		private function isEnd():Boolean {
			for(var i:int = 0;i < 16; i++)
				if(null == boxes[i])
					return false;
			
			for(var i:int = 0;i < 16;i ++) {
				if(0 == (i % 4))
					continue;
				if(boxes[LEFT[i]].getVal() == boxes[LEFT[i-1]].getVal())
					return false;
			}
			
			for(var i:int = 0;i < 16;i ++) {
				if(0 == (i % 4))
					continue;
				if(boxes[UP[i]].getVal() == boxes[UP[i-1]].getVal())
					return false;
			}
			
			return true;
		}
		
		public function isAddRandom():Boolean {
			return true;
		}
		
		public function keyDown(e:KeyboardEvent):void {
			trace(e);
			if(e.keyCode == Keyboard.E) {
				end = new End();
				this.addChild(end);
				end.bu_again.addEventListener(MouseEvent.CLICK, Restart);
				return ;
			}
			
			if(e.keyCode > 40 || e.keyCode < 37)
				return ;
			
			if(e.keyCode == Keyboard.UP)
				move.init(0, -1);
			else if(e.keyCode == Keyboard.DOWN)
				move.init(0, 1);
			else if(e.keyCode == Keyboard.LEFT)
				move.init(-1, 0);
			else if(e.keyCode == Keyboard.RIGHT)
				move.init(1, 0);
			
			change = false;
			
			for(var i:int = 0; i < 16; i++)
				modified[i] = false;
			
			var index:Array ;
			switch(e.keyCode) {
				case Keyboard.UP:
					index = UP;
					break;
				case Keyboard.DOWN:
					index = DOWN;
					break;
				case Keyboard.LEFT:
					index = LEFT;
					break;
				case Keyboard.RIGHT:
					index = RIGHT;
					break;
			}
			
			for( var i :int = 0 ; i < 16; i++) {
				if(0 == i % 4)
					continue;
				if(boxes[index[i]])
					putDown(index, i);
			}
			
			if(true == change) {
				for(i = 0;i < 16; i ++) {
					if(true == modified[i]) {
						mp3_hit.play();
						break;
					}
				}
				if(16 == i) 
					mp3_move.play();
			}
			
			this.move.startMove();
			if(true == isEnd()) {
				trace("end");
				end = new End();
				this.addChild(end);
				end.bu_again.addEventListener(MouseEvent.CLICK, Restart);
				return ;
			}
			trace("score", score);
		}
		
		private function del(pos:int) {
			if(null == boxes[pos])
				return ;
			this.removeChild(boxes[pos]);
			boxes[pos] = null;
		}
		
		private function add(pos:int, val:int) {
			change = true;
			trace(pos, val);
			var tmp:Box = new Box(val);
			tmp.x = layout_x[pos] + map_x;
			tmp.y = layout_y[pos] + map_y;
			boxes[pos] = tmp;
			this.addChild(boxes[pos]);
		}
		
		public function random() {
			var pos:int = Math.random() * 16;
			while(null != boxes[pos])
				pos = Math.random() * 16;
			
			var val:int = 1;
			if(Math.random() < 0.1)
				val ++;
			add(pos, val);
			addbox.addRandom(pos);
		}
		
		private function start() {
			this.score = 0;
			title.score.updateName(this.score.toString());
			boxes = new Array();
			
			for(var i:int = 0; i < 16; i++) {
				var tmp:Box = new Box();
				tmp.x = layout_x[i] + map_x;
				tmp.y = layout_y[i] + map_y;
				this.addChild(tmp);
				boxes[i] = null;
			}
		
			this.random();
			this.random();
		}
	}
}