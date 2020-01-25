// =======================================
// class ArrayList Implementation
// =======================================
ArrayList::ArrayList()
{
	// initialize lastIndex as -1.
	// -1 means that the list does not use any index in list array
	lastIndex = -1;
}

void ArrayList::AddElement( string x )
{
	lastIndex++;
	list[lastIndex] = x;
}

void ArrayList::DeleteElement() {
	lastIndex--;
}
