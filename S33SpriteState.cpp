#include "S33Scene.h"
#include "S33Sprite.h"
#include "S33SpriteState.h"

namespace Soshiant33
{
	S33SpriteState::S33SpriteState(const char* name)
	{
		this->mesh = 0;
		this->frameTimeLenght = 1000/30;
		this->totalFrames = 0;
		this->currentFrame = 0;
		this->extraFrameTime =0;
		if(name)
			this->name = name;
		else
			this->name = "who.am.i";	
	}
	S33KeyFrame* S33SpriteState::AddKeyFrame(int subsetIndex)
	{
		S33KeyFrame* keyframe = new S33KeyFrame(subsetIndex);
		this->timeline.push_back(keyframe);
		this->totalFrames ++;
		return keyframe;
	}
	void S33SpriteState::RemoveKeyFrame(unsigned short index)
	{
		delete this->timeline[index];
		this->timeline.erase(this->timeline.begin()+index);
		this->totalFrames --;
	}
	void S33SpriteState::SetGraphic(const char* name)
	{
		if(name)
		{
			this->graphic = name;
			this->mesh = SPResourceManager::GetMesh(name);
		}
	}
	S33SpriteState::~S33SpriteState()
	{
		std::vector<S33KeyFrame*>::iterator timelineIterator = this->timeline.begin();
		while(timelineIterator != this->timeline.end())
			delete (*timelineIterator++);
	}

	void S33SpriteState::Render(S33Sprite* instance)
	{
		if (this->totalFrames)
		{
			this->extraFrameTime += instance->scene->timeStep ;
			short plusFrames = this->extraFrameTime / this->frameTimeLenght;

			if(plusFrames)
			{
				plusFrames %= this->totalFrames;
				this->currentFrame += plusFrames;
				if(this->currentFrame < 0)
					this->currentFrame += this->totalFrames ;
				this->currentFrame %= this->totalFrames;
				this->extraFrameTime %= this->frameTimeLenght;

				//std::cout <<"time step is : "<< instance->scene->timeStep  << " | frame tme lenght is : " << this->frameTimeLenght <<" | current frame is : " << this->currentFrame << "\n";
			}
			if(this->timeline[this->currentFrame]->hasAction)
			{
				//Execute Action
			}
			this->mesh->SetCurrentSubsetIndex(this->timeline[this->currentFrame]->subsetIndex);
			this->mesh->Render(&instance->ep);
		}
	}
	void S33SpriteState::serialize(SPArchive& archive)
	{
		archive & this->frameTimeLenght;
		archive & this->totalFrames;
		archive & this->currentFrame;
		archive & this->name;
		archive & this->graphic;
		archive & this->timeline;
		if(archive.ioType == SPArchive::IO_Input)
			this->SetGraphic(this->graphic.c_str());
	}
}