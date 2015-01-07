package
{
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.ui.Keyboard;
	
	[SWF(width = "620", height = "720", frameRate = "60")]

	public class Main extends Sprite {
		
		private var m_gameworld 	:GameWorld;
		
		public function Main() {
			if(stage)
				AddToStage(null);
			else
				addEventListener(Event.ADDED_TO_STAGE, AddToStage);
		}
		
		private function AddToStage(e:Event):void {
			m_gameworld = new GameWorld();
			stage.addChild(m_gameworld);
			
			stage.color = 0xfaf8ef;
			stage.addEventListener(KeyboardEvent.KEY_DOWN, m_gameworld.keyDown);
			stage.addEventListener(Event.ENTER_FRAME, m_gameworld.move.changePos);
			stage.addEventListener(Event.ENTER_FRAME, m_gameworld.addbox.changeScale);
		}
	}
}