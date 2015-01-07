package
{
	import flash.events.Event;

	public class Move {
		private var gameworld		:GameWorld; 
		private var speed			:Number;
		public var isMoved 			:Boolean;
		private var fromx			:Array;
		private var fromy			:Array;
		private var tox				:Array;
		private var toy				:Array;
		private var pos				:Array;
		private var dx				:int;
		private var dy 				:int;
		private var addSpeed		:Number;
		
		public function Move(father:GameWorld) {
			this.gameworld = father; 
			this.addSpeed = 3;
			this.isMoved = false;
		}
		
		public function init(dx:int ,dy:int):void {
			this.speed = 0;
			isMoved = false;
			fromx = new Array();
			fromy = new Array();
			tox = new Array();
			toy = new Array();
			pos = new Array();
		
			this.dx = dx;
			this.dy = dy;
		}
		
		public function addMoveObject(a:int, b:int, c:int, d:int, pos:int):void {
			this.fromx.push(a);
			this.fromy.push(b);
			this.tox.push(c);
			this.toy.push(d);
			this.pos.push(pos);
		}
		
		public function startMove():void {
			isMoved = true;
		}
		
		private function arrive(pos:int):Boolean {
			if(0 == dx && 1 == dy) {
				if(fromy[pos] >= toy[pos])
					return true;
			}
			else if(0 == dx && -1 == dy) {
				if(fromy[pos] <= toy[pos])
					return true;
			}
			else if(1 == dx && 0 == dy) {
				if(fromx[pos] >= tox[pos])
					return true;
			}
			else if(-1 == dx && 0 == dy) {
				if(fromx[pos] <= tox[pos])
					return true;
			}
			return false;
		}
		
		public function changePos(e:Event):void {
	//		trace(this.isMoved);
			if(false == isMoved)
				return ;
			
			speed += addSpeed;
			
			var unfinished		:int = 0;
			for( var i:int = 0; i < fromx.length; i++) {
				
				fromx[i] += dx * speed;
				fromy[i] += dy * speed;
				gameworld.boxes[pos[i]].x = fromx[i];
				gameworld.boxes[pos[i]].y = fromy[i];
		
				if(false == arrive(i))
					unfinished ++;
				else {
					gameworld.boxes[pos[i]].x = tox[i];
					gameworld.boxes[pos[i]].y = toy[i];
				}
			}
			
			if(0 == unfinished) {
				this.isMoved = false;
				trace("move successfully");
				if(true == gameworld.change)
					gameworld.random();
			}
		}
	}
}