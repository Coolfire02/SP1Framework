#include "Bucket.h"

std::string Bucket::getType()
{
	return "Bucket";
}

Bucket::Bucket()
{
	art.setArt(BUCKET_ART);
	weight = 1000;
}

Bucket::~Bucket()
{

}