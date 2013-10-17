#include "Ent.h"

CEnt::CEnt()
{
	CGEntity();
	parent=nullptr;
}
CEnt::CEnt(btVector3& startposition)
{
	CGEntity();
	transform.setOrigin(startposition);
	parent=nullptr;
}
CEnt::CEnt(btVector3& startposition,btQuaternion& startrotation)
{
	CGEntity();
	transform.setOrigin(startposition);
	transform.setRotation(startrotation);
	parent=nullptr;
}
CEnt::CEnt(btVector3& startposition,btVector3& startrotation)
{
	CGEntity();
	transform.setOrigin(startposition);
	transform.setRotation(btQuaternion(startrotation.x(),startrotation.y(),startrotation.z()));
	parent=nullptr;
}
void CEnt::Init(string newname)
{
	CGEntity::Init(newname);
	SetType("CEnt");
}
void CEnt::Frame()
{

	//Loop through all attachment points.
	int sz = attachmentpoints.size();
	for(int i = 0;i<sz;i++)
	{
		//Update all attached entities with the transform of the attachment point.
		SAttachmentPoint* point = attachmentpoints[i];
		int sze = point->attached.size();
		for(int j = 0;j<sze;j++)
		{
			point->attached[j]->transform.setOrigin(btVector3(point->currentset->transform->p[0],point->currentset->transform->p[1],point->currentset->transform->p[2]));
			point->attached[j]->transform.setRotation(btQuaternion(point->currentset->transform->r[0],point->currentset->transform->r[1],point->currentset->transform->r[2]));
		}
		//Update the animset.
		SANIMSET* set = point->currentset;
		int framecount = set->frames;
		int cf = (int)floorf(set->frame);
		//Non-interpolated frames are drawn here at ANIM_RATE frames per second.
		set->transform = set->anim[cf];
		set->frame+=(Graphics.deltaTime*ANIM_RATE);
		if(set->frame>=(float)framecount+1.0f)
		{
			set->frame=0.0f;
		}
	}
}
void CEnt::Attach(CEnt* attachable,string attachmentpoint)
{
	//Attach a CEnt to an attachment point located on the object.
	int sz = attachmentpoints.size();
	for(int i = 0;i<sz;i++)
	{
		if(attachmentpoints[i]->name==attachmentpoint)
		{
			attachmentpoints[i]->attached.push_back(attachable);
			attachable->parent=this;
		}
	}
}
void CEnt::ProcessAttachFile(string filename)
{
	//Process a file...
	//This function reads an attachment point file and adds in all attachments (bones) and their associated frames.
	ifstream file(filename.c_str(),ios::in|ios::binary);
	int points = filereadint(&file);
	for(int i = 0;i<points;i++)
	{
		//Load in the points.
		SAttachmentPoint* point = new SAttachmentPoint();
		int lstr = filereadint(&file);
		point->name = filereadstring(&file,lstr);
		point->sets=filereadint(&file);;
		point->animset = new SANIMSET*[point->sets];
		for(int j = 0;j<point->sets;j++)
		{
			point->animset[j] = new SANIMSET();
			SANIMSET* anim = point->animset[j];
			int alstr = filereadint(&file);
			anim->name=filereadstring(&file,alstr);
			anim->frames=filereadint(&file);
			anim->anim = new SANIMFRAME*[anim->frames];
			for(int k = 0;k<anim->frames;k++)
			{
				anim->anim[k] = new SANIMFRAME();
			}
			file.read((char*)(anim->anim),sizeof(SANIMFRAME)*anim->frames);
		}
		attachmentpoints.push_back(point);
	}
}
void CEnt::Terminate()
{
}