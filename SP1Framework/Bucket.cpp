#include "Bucket.h"

std::string Bucket::getType()
{
	return "Bucket";
}

Bucket::Bucket()
{
	art.setArt(BUCKET_ART);
	weight = 0;
}

Bucket::~Bucket()
{

}