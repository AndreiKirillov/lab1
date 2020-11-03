#pragma once
class Pipe
{
private:
	int id;
	int length;
	int diametr;
	bool remont;
public:
	Pipe();
	int GetID() const;
	void SetID(int new_id);
	int GetLength() const;
	void SetLength(int new_length);
	int GetDiametr() const;
	void SetDiametr(int new_diametr);
	void ChangeStatus();
};

