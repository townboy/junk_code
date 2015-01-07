package
{
	import flash.display.Sprite;
	import flash.events.MouseEvent;
	import flash.text.ReturnKeyLabel;
	import flash.ui.Mouse;
	
	
	public class End extends Sprite {
		public var bu_again:DisplayBox;
		
		public function End() {
			this.graphics.beginFill(0xefe5db, 0.6);
			this.graphics.drawRect(0, 0, 620, 720);
			this.graphics.endFill();
			
			this.addChild(new Text(65, "Game Over!",130, 300, 0x776e65));
			
			bu_again = new DisplayBox(110, 40, 0x8f7a66, 
				new Text(20, "Try again",4, 7, 0xefe5db));
			this.addChild(bu_again);
			bu_again.x = 200;
			bu_again.y = 450;
			bu_again.useHandCursor = true;
			bu_again.buttonMode = true;
		}
		
	}
}