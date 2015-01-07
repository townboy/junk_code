package
{
	import flash.events.Event;

	public class AddBox {
		private var gameworld	:GameWorld;
		private var limit		:int = 10;
		
		private var pos 		:Array;
		private var left		:Array;
		
		
		public function AddBox(father:GameWorld) {
			gameworld = father;
			pos = new Array();
			left = new Array();
		}
		
		public function addRandom(pos :int):void {
			trace("add random", pos);
			this.pos.push(pos);
			this.left.push(this.limit);
			gameworld.boxes[pos].x += 50;
			gameworld.boxes[pos].y += 50;	
		}
		
		public function changeScale(e:Event):void  {
			for(var i:int = 0;i < this.pos.length; i++) {
				if(0 == left[i] || (null == gameworld.boxes[pos[i]])) {
					pos.shift();
					left.shift();
					i --;
					continue;
				}
				left[i] --;
				gameworld.boxes[pos[i]].scaleX = 1 - left[i] / 10;
				gameworld.boxes[pos[i]].scaleY = 1 - left[i] / 10;
				gameworld.boxes[pos[i]].x -= 5;
				gameworld.boxes[pos[i]].y -= 5;
			}
		
		}
		
	}
}