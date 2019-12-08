#include "csci152_student.h"
#include <iostream>



csci152_student::csci152_student(
		std::string nm,
		unsigned int *asmts,
		unsigned int num_qs,
		unsigned int *quizzes,
		unsigned int final_exam

):
name(nm),
assignment_scores(new unsigned int[4]),
num_of_quizzes(num_qs),
quiz_scores(new unsigned int[num_qs]),
final_exam_score(final_exam)


{


	for(size_t num = 0; num < 4; num++)

	{
		assignment_scores[num] = asmts[num];
	}


	for(size_t num = 0; num < num_qs; num++)

	{
		quiz_scores[num] = quizzes[num];
	}
}

/*
 * Copy constructor
 */
csci152_student::csci152_student(const csci152_student& other):
					name(other.name),
					assignment_scores(new unsigned int [4]),
					num_of_quizzes(other.num_of_quizzes),
					quiz_scores(new unsigned int [num_of_quizzes]),
					final_exam_score(other.final_exam_score)
{


	for(size_t num = 0; num < 4; num++)

	{
		assignment_scores[num] = other.assignment_scores[num];
	}
	for(size_t num = 0; num < num_of_quizzes; num++)

	{
		quiz_scores[num] = other.quiz_scores[num];
	}

}

/*
 * Copy assignment - be careful to properly dispose of allocated memory for this
 * before overwriting with values from other
 */
csci152_student& csci152_student::operator=(const csci152_student& other){
	name = other.name;
	delete[] assignment_scores;
	assignment_scores =new unsigned int [4];

	if (num_of_quizzes!= other.num_of_quizzes) {
		num_of_quizzes=other.num_of_quizzes;
	delete[] quiz_scores;
	quiz_scores=new unsigned int[num_of_quizzes];}
	final_exam_score = other.final_exam_score;

	for(size_t num = 0; num < 4; num++)

	{
		assignment_scores[num] = other.assignment_scores[num];
	}
	for(size_t num = 0; num < num_of_quizzes; num++)

	{
		quiz_scores[num] = other.quiz_scores[num];
	}

	return *this;
}
/*
 * Name getter
 */
std::string csci152_student::get_name() const
{
	return name;
}

/*
 * Calculates the average assignment score, between 0.0 and 100.0
 */
double csci152_student::calculate_assignment_perc() const

{
	int assign_num;
	double average, sum = 0;

	for (assign_num = 0; assign_num < 4; assign_num++)

	{
		sum += assignment_scores[assign_num];
	}

	average = sum / 4;
	return average;

}

/*
 * Calculates the total quiz percentage, where the lowest score is dropped from
 * from the calculation.  Between 0.0 and 100.0
 */
double csci152_student::calculate_quiz_perc() const
{
	unsigned int quiz_num=0;
	int min_num = 0;
	double average, sum = 0;

	for (size_t i = 0; i < num_of_quizzes; i++) {
		if (quiz_scores[i] < quiz_scores[min_num]) {
			min_num = i;
		}
	}

	while (quiz_num < num_of_quizzes)
	{
		sum += quiz_scores[quiz_num];
		++quiz_num;
	}

	average = (sum - quiz_scores[min_num]) / (num_of_quizzes - 1);
	return average*100/15;
}


/*
 * Returns the value stored in final_exam_score
 */
unsigned int csci152_student::get_final_exam_perc() const
{
	return final_exam_score;

}

/*
 * Calculates the total course grade as a percent, using the weighting from
 * the syllabus
 */
double csci152_student::calculate_course_perc() const
{
	double course_total = (csci152_student::calculate_assignment_perc()*20/100 )+ (csci152_student::calculate_quiz_perc()*0.4) + (csci152_student::get_final_exam_perc()*40/100);

	return course_total;
}

/*
 * Destructor - don't forget you need to delete anything you explicitly allocated
 */
csci152_student::~csci152_student() {
	delete[] assignment_scores;
	delete[] quiz_scores;
}

