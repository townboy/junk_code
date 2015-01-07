package
{
	import flash.display.Sprite;
	import flash.text.TextField;
	import flash.text.TextFormat;
	
	public class Title extends Sprite {
		
		public var best		:DisplayBox;
		public var score	:DisplayBox;
		public var newGame 	:DisplayBox;
		
		
		// xuyao gaixie
		public function Title(map_x :int):void {
		
			this.addChild(new Text(75, "2048", map_x, 10, 0x766e64));
			this.addChild(new Text(18, "Play 2048 Game Locally", map_x, 85, 0x766e64));
			this.addChild(new Text(15, "Join the numbers and get to the ", map_x, 105, 0x766e64, false)); 
			this.addChild(new Text(15, "2048 tile!", 310, 105, 0x766e64));
			this.addButton();
		}
		
		private function addButton():void {
			
			var best_text_up:TextField = new Text(15, "BEST", 30, 0, 0xfaf8ef);
			var score_text_up:TextField = new Text(15, "SCORE", 30, 0, 0xfaf8ef);
			var newGame_text:TextField = new Text(20, "New Game", 5, 5, 0xf9f6f2);
			
			var best_text_down:TextField = new Text(22, "0", 40, 20, 0xffffff);
			var score_text_down:TextField = new Text(22, "0", 30, 20, 0xffffff);
	
		    best= new DisplayBox(100, 50, 0xbbada1, best_text_up, best_text_down);
			score = new DisplayBox(100, 50, 0xbbada1, score_text_up, score_text_down);
			newGame = new DisplayBox(100, 40, 0x8f7a66, newGame_text);	
			
			best.x = 450;
			best.y = 30;
			
			score.x = 340;
			score.y = 30;
			
			newGame.x = 450;
			newGame.y = 90;
			
			this.addChild(best);
			this.addChild(score);
			this.addChild(newGame);
			newGame.useHandCursor = true;
			newGame.buttonMode = true;
		}
	}
}