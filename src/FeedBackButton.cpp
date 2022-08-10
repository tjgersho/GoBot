 
#include "FeedBackButton.hpp" 
#include "SensorWindow.hpp"
 
void FeedBackButton::drawSelf(SensorWindow * screen){

	if (!this->pressed) {
      
		SDL_SetRenderDrawColor(screen->mRenderer, this->color.r, this->color.g, this->color.b, this->color.a);
		SDL_RenderFillRect(screen->mRenderer, &this->draw_rect);
        // std::ostringstream  stringStream;
		// stringStream << _label;
		// std::string copyOfStr = stringStream.str();
		SDL_Color textColor = { 0x00, 0x00, 0x00 };
		if (screen->feedbackNoButtonText->m_texture->loadFromRenderedText(_label, textColor)) {
			//    printf("Failed to render text texture!\n");
		}
		screen->feedbackNoButtonText->m_texture->render( this->draw_rect.x + 10,  this->draw_rect.y +  this->draw_rect.h/2-10);
	}

}