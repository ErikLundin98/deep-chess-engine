#ifndef SIGMANET_H
#define SIGMANET_H

#include <torch/torch.h>
#include <chess/chess.hpp>
#include <utility>

class residual_block : public torch::nn::Module {

    torch::nn::Conv2d conv1 = nullptr;
    torch::nn::BatchNorm2d batchnorm1 = nullptr;
    torch::nn::Conv2d conv2 = nullptr;
    torch::nn::BatchNorm2d batchnorm2 = nullptr;

public:

    residual_block(int filters);

    torch::Tensor forward(torch::Tensor x);

};


class sigmanet : public torch::nn::Module {

    int history;
    int in_channels;
    int filters;
    int blocks;

    torch::nn::Sequential input_conv = nullptr;
    torch::nn::Sequential residual = nullptr;
    torch::nn::Sequential value_head = nullptr;
    torch::nn::Sequential policy_head = nullptr;

    static const int feature_planes = 6 + 6 + 2; // p1 piece, p2 piece, repetitions
    static const int constant_planes = 1 + 1 + 2 + 2 + 1; // colour, total move count, p1 castling, p2 castling, no-progress count

public:

    sigmanet(int history = 8, int filters = 64, int blocks = 10);

    std::pair<torch::Tensor, torch::Tensor> forward(torch::Tensor x);

    torch::Tensor encode_input(const chess::game& g);

    int get_input_channels() const;
};

torch::Tensor sigma_loss(torch::Tensor z, torch::Tensor v, torch::Tensor pi, torch::Tensor p);

torch::Tensor bitboard_plane(chess::bitboard bb);

#endif