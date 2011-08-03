#ifndef __ANALYSIS_H__
#define __ANALYSIS_H__

class Analysis {
	public:
		Analysis();
		Analysis(Analysis &a);
		~Analysis();

		void setType(int type) { this->type = type; };
		int getType() { return this->type; };

		void setParam(const char *param);
		char *getParam() { return this->param; };

		enum Type {
			DC,
			AC,
			TRANS
		};
	private:
		int type;
		char *param;
};

#endif // __ANALYSIS_H__
